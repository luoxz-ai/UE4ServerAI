# -*- coding: gbk -*-
from xml.dom.minidom import parse
import xml.dom.minidom
import sys

HOST_FILE = 'GenServerCode.xml'

# BTManagerName = 'CUE4BTManager'
BTManagerName = ''

agentFuncs = set([])
agentFuncsParas = {}

BBList = ['', '2', '3', '4', '5', '6']
def node_add_attribute(node, content_add):
    for idx in BBList:
        BlackboardKey = node.getAttribute('BlackboardKey' + idx)
        if BlackboardKey:
            content_add += 'ADD_ATTRIBUTE(Str, BlackboardKey' + idx + ')\n'
        else:
            break
    
    return content_add

def class_h_add_attribute(node, fileContent_h):
    for idx in BBList:
        BlackboardKey = node.getAttribute('BlackboardKey' + idx)
        if BlackboardKey:
            fileContent_h += '    FString BlackboardKey' + idx + ';\n'
        else:
            break
    
    return fileContent_h

def func_para_def_add_attribute(node, para_content):
    para_content += 'void* Node'
    for idx in BBList:
        BlackboardKey = node.getAttribute('BlackboardKey' + idx)
        if BlackboardKey:
            para_content += ', '
            para_content += 'const char* BlackboardKey' + idx
        else:
            break
    
    return para_content

def func_para_use_add_attribute(node, para_content, agent_use):
    if agent_use:
        para_content += 'Node'
    else:
        para_content += 'this'
    for idx in BBList:
        BlackboardKey = node.getAttribute('BlackboardKey' + idx)
        if BlackboardKey:
            para_content += ', '
            if agent_use:
                para_content += 'BlackboardKey' + idx
            else:
                para_content += 'BlackboardKey' + idx + '.c_str()'
        else:
            break
    
    return para_content

def clearcode(path,find_str_begin,find_str_end):
    file_r = open( path, "r" )  
    content_all = file_r.read()
    file_r.close()
    pos = content_all.find(find_str_begin)
    pos_end = content_all.find(find_str_end)
    content_all = content_all.decode('GBK')
    if pos != -1:  
        content_all = content_all[:pos] + find_str_begin + content_all[pos_end:]  
        file_w = open( path, "w" ) 
        file_w.write( content_all.encode('GBK') )
        file_w.close() 

def addcode(path,content_add,find_str):
    file_r = open( path, "r" )  
    content_all = file_r.read()
    file_r.close()
    pos = content_all.find(find_str)
    content_all = content_all.decode('GBK')
    if pos != -1:  
        content_all = content_all[:pos] + content_add + content_all[pos:]  
        file_w = open( path, "w" ) 
        file_w.write( content_all.encode('GBK') )
        file_w.close() 

def ReadDOMTree(hostFile):
    file = open(hostFile, 'r+')
    dstr = file.read()
    file.close()
    DOMTree = xml.dom.minidom.parseString(dstr)
    return DOMTree

def GenServices():
    global BTManagerName
    DOMTree = ReadDOMTree(HOST_FILE)

    for node in DOMTree.getElementsByTagName('service'):
        buildin = node.getAttribute('buildin')
        if buildin == 'yes':
            continue
        name = node.getAttribute('name')
        tickfunc = node.getAttribute('tickfunc')
        OnBecomeRelevant = node.getAttribute('OnBecomeRelevant')
        agent = node.getAttribute('agent')
        fileName_h = name + ".h"
        fileName_cpp = name + ".cpp"
        fileContent_h = '''
#pragma once

#include "BehaviorTree/BTService.h"

class UBTService_Example: public UBTService
{
public:
    UBTService_Example();
'''
        fileContent_h = class_h_add_attribute(node, fileContent_h)

        fileContent_h = fileContent_h.replace("BTService_Example", name)
        if OnBecomeRelevant:
            OnBecomeRelevant_h ='''
    /** called when auxiliary node becomes active
     * this function should be considered as const (don't modify state of object) if node is not instanced! */
    virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
'''
            fileContent_h += OnBecomeRelevant_h

        fileContent_h +='''
protected:
'''
        fileContent_h = fileContent_h.replace("BTService_Example", name)
        if tickfunc:
            tickfunc_h ='''
    /** update next tick interval
    * this function should be considered as const (don't modify state of object) if node is not instanced! */
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
'''
            fileContent_h += tickfunc_h

        fileContent_h +='''
};
'''
        WriteToFile('..\BehaviorTree\Services\\'+fileName_h, fileContent_h)

        fileContent_cpp = '''
#include "BehaviorTree/Services/BTService_Example.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/AIMessageTypes.h"
#include "BehaviorTree/Blackboard/TdrReflectionErr.h"
#include "BehaviorTree/BehaviorTreeParseHelper.h"
'''
        if BTManagerName:
            fileContent_cpp +='''
#include "../../../ai/BTManagerType.h"
'''
            fileContent_cpp = fileContent_cpp.replace("BTManagerType", BTManagerName)

        content_add = '''
BEGIN_DERIVED_NODE_FACTORY(UBTService_Example, UBTService_Example_Factory, ServiceNodeFactoryBase)
'''
        content_add = node_add_attribute(node, content_add)

        content_add += '''END_DERIVED_NODE_FACTORY(UBTService_Example, UBTService_Example_Factory)
'''
        fileContent_cpp += content_add
        fileContent_cpp +=''' 
UBTService_Example::UBTService_Example() : UBTService()
{
    NodeName = "BTService_Example";
'''
        if OnBecomeRelevant:
            fileContent_cpp += '''
    bNotifyBecomeRelevant = true;
'''

        fileContent_cpp += '''
}
'''
        fileContent_cpp = fileContent_cpp.replace("BTService_Example", name)
        if tickfunc:
            tickfunc_cpp ='''
void UBTService_Example::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    UBTService::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    //if (OwnerComp.GetBTManager())
    //{
    //    ((MAYEX::CUE4BTManager*)(OwnerComp.GetBTManager()))->TickFuncName();
    //}
}
'''
            tickfunc_cpp = tickfunc_cpp.replace("BTService_Example", name)
            if BTManagerName:
                tickfunc_cpp = tickfunc_cpp.replace("//", "")
            para_content = ''
            para_content = func_para_use_add_attribute(node, para_content, False)
            tickfunc_cpp = tickfunc_cpp.replace("TickFuncName()", tickfunc + '(' + para_content + ')')
            fileContent_cpp += tickfunc_cpp

            agentFuncs.add(tickfunc)
            para_def_content = ''
            para_def_content = func_para_def_add_attribute(node, para_def_content)

            para_content = ''
            para_content = func_para_use_add_attribute(node, para_content, True)
            agentFuncsParas[tickfunc] = {'func_para_use':para_content, 'func_para_def':para_def_content}
            agentFuncsParas[tickfunc]['func_return_type'] = 'void'

        if OnBecomeRelevant:
            OnBecomeRelevant_cpp ='''
void UBTService_Example::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    //if (OwnerComp.GetBTManager())
    //{
    //    ((MAYEX::CUE4BTManager*)(OwnerComp.GetBTManager()))->OnBecomeRelevantName();
    //}
}
'''
            OnBecomeRelevant_cpp = OnBecomeRelevant_cpp.replace("BTService_Example", name)
            if BTManagerName:
                OnBecomeRelevant_cpp = OnBecomeRelevant_cpp.replace("//", "")
            para_content = ''
            para_content = func_para_use_add_attribute(node, para_content, False)
            OnBecomeRelevant_cpp = OnBecomeRelevant_cpp.replace("OnBecomeRelevantName()", OnBecomeRelevant + '(' + para_content + ')')
            fileContent_cpp += OnBecomeRelevant_cpp

            agentFuncs.add(OnBecomeRelevant)
            para_def_content = ''
            para_def_content = func_para_def_add_attribute(node, para_def_content)

            para_content = ''
            para_content = func_para_use_add_attribute(node, para_content, True)
            agentFuncsParas[OnBecomeRelevant] = {'func_para_use':para_content, 'func_para_def':para_def_content}
            agentFuncsParas[OnBecomeRelevant]['func_return_type'] = 'void'

        WriteToFile('..\BehaviorTree\Services\\'+fileName_cpp, fileContent_cpp)

    

def GenTasks():
    global BTManagerName
    DOMTree = ReadDOMTree(HOST_FILE)

    for node in DOMTree.getElementsByTagName('task'):
        buildin = node.getAttribute('buildin')
        if buildin == 'yes':
            continue
        name = node.getAttribute('name')
        tickfunc = node.getAttribute('tickfunc')
        enterfunc = node.getAttribute('enterfunc')
        exitfunc = node.getAttribute('exitfunc')
        abortfunc = node.getAttribute('abortfunc')
        agent = node.getAttribute('agent')
        fileName_h = name + ".h"
        fileName_cpp = name + ".cpp"
        fileContent_h = '''
#pragma once

#include "BehaviorTree/BTTaskNode.h"

class UBTTask_Example: public UBTTaskNode
{
public:
    UBTTask_Example();

'''
        fileContent_h = fileContent_h.replace("BTTask_Example", name)
        if enterfunc:
            enterfunc_h ='''
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
'''
            fileContent_h += enterfunc_h

        if exitfunc:
            exitfunc_h ='''
    virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult);
'''
            fileContent_h += exitfunc_h

        fileContent_h = class_h_add_attribute(node, fileContent_h)

        if tickfunc:
            tickfunc_h ='''
protected:
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

'''
            fileContent_h += tickfunc_h

        if abortfunc:
            abortfunc_h ='''
protected:
    virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

'''
            fileContent_h += abortfunc_h

        fileContent_h +='''
};
'''
        WriteToFile('..\BehaviorTree\Tasks\\'+fileName_h, fileContent_h)

        fileContent_cpp = '''
#include "BehaviorTree/Tasks/BTTask_Example.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeParseHelper.h"
'''
        if BTManagerName:
            fileContent_cpp +='''
#include "../../../ai/BTManagerType.h"
'''
            fileContent_cpp = fileContent_cpp.replace("BTManagerType", BTManagerName)

        content_add = '''
BEGIN_DERIVED_NODE_FACTORY(UBTTask_Example, UBTTask_Example_Factory, TaskNodeFactoryBase)
'''

        content_add = node_add_attribute(node, content_add)

        content_add += '''END_DERIVED_NODE_FACTORY(UBTTask_Example, UBTTask_Example_Factory)
'''
        fileContent_cpp += content_add
        fileContent_cpp +='''
UBTTask_Example::UBTTask_Example() : UBTTaskNode()
{
    NodeName = "Talk";

    bNotifyTick = false;

    bNotifyTaskFinished = false;
}
'''
        if tickfunc:
            fileContent_cpp = fileContent_cpp.replace("bNotifyTick = false", "bNotifyTick = true")
        if exitfunc:
            fileContent_cpp = fileContent_cpp.replace("bNotifyTaskFinished = false", "bNotifyTaskFinished = true")

        fileContent_cpp = fileContent_cpp.replace("BTTask_Example", name)
        if enterfunc:
            enterfunc_cpp ='''
EBTNodeResult::Type UBTTask_Example::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    int iRet = EBTNodeResult::Succeeded;
    //if (OwnerComp.GetBTManager())
    //{
    //    iRet = ((MAYEX::CUE4BTManager*)(OwnerComp.GetBTManager()))->EnterFuncName();
    //}

    return (EBTNodeResult::Type)iRet;
}
'''
            enterfunc_cpp = enterfunc_cpp.replace("BTTask_Example", name)
            if BTManagerName:
                enterfunc_cpp = enterfunc_cpp.replace("//", "")
            para_content = ''
            para_content = func_para_use_add_attribute(node, para_content, False)
            enterfunc_cpp = enterfunc_cpp.replace("EnterFuncName()", enterfunc + '(' + para_content + ')')
            fileContent_cpp += enterfunc_cpp
            agentFuncs.add(enterfunc)
            para_def_content = ''
            para_def_content = func_para_def_add_attribute(node, para_def_content)

            para_content = ''
            para_content = func_para_use_add_attribute(node, para_content, True)
            agentFuncsParas[enterfunc] = {'func_para_use':para_content, 'func_para_def':para_def_content}
            agentFuncsParas[enterfunc]['func_return_type'] = 'int'

        if exitfunc:
            exitfunc_cpp ='''
void UBTTask_Example::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
    //if (OwnerComp.GetBTManager())
    //{
    //    ((MAYEX::CUE4BTManager*)(OwnerComp.GetBTManager()))->ExitFuncName();
    //}
}
'''
            exitfunc_cpp = exitfunc_cpp.replace("BTTask_Example", name)
            if BTManagerName:
                exitfunc_cpp = exitfunc_cpp.replace("//", "")
            para_content = ''
            para_content = func_para_use_add_attribute(node, para_content, False)
            exitfunc_cpp = exitfunc_cpp.replace("ExitFuncName()", exitfunc + '(' + para_content + ')')
            fileContent_cpp += exitfunc_cpp
            agentFuncs.add(exitfunc)
            para_def_content = ''
            para_def_content = func_para_def_add_attribute(node, para_def_content)

            para_content = ''
            para_content = func_para_use_add_attribute(node, para_content, True)
            agentFuncsParas[exitfunc] = {'func_para_use':para_content, 'func_para_def':para_def_content}
            agentFuncsParas[exitfunc]['func_return_type'] = 'void'

        if tickfunc:
            tickfunc_cpp ='''
void UBTTask_Example::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    EBTNodeResult::Type iRet = EBTNodeResult::Succeeded;
    //if (OwnerComp.GetBTManager())
    //{
    //    iRet = (EBTNodeResult::Type)((MAYEX::CUE4BTManager*)(OwnerComp.GetBTManager()))->TickFuncName();
    //}

    if (iRet != EBTNodeResult::InProgress)
    {
        FinishLatentTask(OwnerComp, iRet);
    }
}
'''
            tickfunc_cpp = tickfunc_cpp.replace("BTTask_Example", name)
            if BTManagerName:
                tickfunc_cpp = tickfunc_cpp.replace("//", "")
            para_content = ""
            para_content = func_para_use_add_attribute(node, para_content, False)
            tickfunc_cpp = tickfunc_cpp.replace("TickFuncName()", tickfunc + '(' + para_content + ')')
            fileContent_cpp += tickfunc_cpp
            agentFuncs.add(tickfunc)
            para_def_content = ''
            para_def_content = func_para_def_add_attribute(node, para_def_content)

            para_content = ''
            para_content = func_para_use_add_attribute(node, para_content, True)
            agentFuncsParas[tickfunc] = {'func_para_use':para_content, 'func_para_def':para_def_content}
            agentFuncsParas[tickfunc]['func_return_type'] = 'int'

        if abortfunc:
            abortfunc_cpp ='''
EBTNodeResult::Type UBTTask_Example::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    int iRet = EBTNodeResult::Aborted;
    //if (OwnerComp.GetBTManager())
    //{
    //    iRet = ((MAYEX::CUE4BTManager*)(OwnerComp.GetBTManager()))->AbortFuncName();
    //}

    return (EBTNodeResult::Type)iRet;
}
'''
            abortfunc_cpp = abortfunc_cpp.replace("BTTask_Example", name)
            if BTManagerName:
                abortfunc_cpp = abortfunc_cpp.replace("//", "")
            para_content = ''
            para_content = func_para_use_add_attribute(node, para_content, False)
            abortfunc_cpp = abortfunc_cpp.replace("AbortFuncName()", abortfunc + '(' + para_content + ')')
            fileContent_cpp += abortfunc_cpp
            agentFuncs.add(abortfunc)
            para_def_content = ''
            para_def_content = func_para_def_add_attribute(node, para_def_content)

            para_content = ''
            para_content = func_para_use_add_attribute(node, para_content, True)
            agentFuncsParas[abortfunc] = {'func_para_use':para_content, 'func_para_def':para_def_content}
            agentFuncsParas[abortfunc]['func_return_type'] = 'int'

        WriteToFile('..\BehaviorTree\Tasks\\'+fileName_cpp, fileContent_cpp)


def WriteToFile(fileName, fileContent):
    f = open(fileName, 'w')
    f.writelines(fileContent)
    f.close()


def main():
    if len(sys.argv) > 1:
        global BTManagerName
        BTManagerName = 'CUE4BTManager'

    GenServices()
    GenTasks()

main()
