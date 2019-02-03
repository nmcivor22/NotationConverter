#include "NotationConverter.hpp"

#include <iostream> 

/****************************************************************************
 *                       INFIX TO POSTFIX
 * *************************************************************************/

std::string NotationConverter::infixToPostfix(std::string infix){
    std::string postfix; //final string
        for(unsigned int i = 0; i < infix.size(); i++){
            std::string str;
            str = infix[i];
            if (infix[i] == OPEN_PARANTH || //push ONTO stack "front of DLL"
                infix[i] == DIV ||
                infix[i] == MULT ){
                frontinsert(str);
            }
            else if (infix[i] == ADD || infix[i] == SUB){ //if top of stack is higher prec POP and then push on stack
                if (((head -> op)[0] == DIV) || ((head -> op)[0] == MULT)){ //delete top of stack
                    postfix = postfix + head -> op + " "; 
                    removefront();
                }
                frontinsert(str);
            }
            else if (infix[i] == CLOSE_PARANTH){
                while ((head -> op)[0] != OPEN_PARANTH && head != NULL){
                    postfix = postfix + head -> op + " ";
                    removefront();
                }
                if (head != NULL) 
                removefront();
            }
            else if ((infix[i] >= 'A' && infix[i] <= 'Z') || (infix[i] >= 'a' && infix[i] <= 'z')){ //send to string
                postfix = postfix + infix[i] + " "; 
            }
            else if (infix[i] != ' '){
                throw std::logic_error("No1");
            }
            else if ((i == infix.size() - 1) && head != NULL){
                while (head != NULL){
                postfix = postfix + head -> op + " ";
                removefront(); 
                }
            }
        }
    return postfix;  
}

/*********************************************************************************
//                        INFIX TO PREFIX
*********************************************************************************/
std::string NotationConverter::infixToPrefix(std::string inStr){
    std::string pre;
    std::string prefix;
    std::string str;
    for(unsigned int i = 0; i < inStr.size(); i++){ //reverse the infix exp by pushing on stack
            str = inStr[i];
            frontinsert(str); 
    }
    while (head  != NULL){ //New reversed infix string
        if (head -> op[0] == OPEN_PARANTH){ //switch the paratheses
            pre = pre + CLOSE_PARANTH + " ";
            removefront();
        }
        else if (head -> op[0] == CLOSE_PARANTH){
            pre = pre + OPEN_PARANTH + " ";
            removefront();
        }
        else{
            pre = pre + head -> op + " ";
            removefront();
        }
    }
    std::string postfix = infixToPostfix(pre); //get postfix of reversed infix string
    for (unsigned int i = 0; i < postfix.size(); i++){
        str = postfix[i];
        frontinsert(str); //push back on stack
    }
    while (head != NULL){
        prefix = prefix + head -> op;
        removefront();
    }
    return prefix;
}
/*********************************************************************************
//                        POSTFIX TO INFIX
*********************************************************************************/
std::string NotationConverter::postfixToInfix(std::string inStr){
    std::string toStack;
    std::string pop1;
    std::string pop2;
    std::string pushit;
    std::string postfixToinfix; 
    
    checkValidInp(inStr);

    for(unsigned int i = 0; i < inStr.size();i++){
        if ((inStr[i] >= 'A' && inStr[i] <= 'Z') || (inStr[i] >= 'a' && inStr[i] <= 'z')){
            toStack = inStr[i];
            frontinsert(toStack);
        }
        else if (inStr[i] == MULT ||inStr[i] == DIV ||inStr[i] == SUB ||inStr[i] == ADD){
                    pop1 = head -> op;
                    removefront();
                    pop2 = head -> op + " ";
                    removefront();
                    pushit = "(" + pop2 + inStr[i] + " " + pop1 + ")";
                    frontinsert(pushit); 
        }
    }
    postfixToinfix = head -> op;
    removefront();
    return postfixToinfix; 
}

/*********************************************************************************
//                        PREFIX TO INFIX
*********************************************************************************/
std::string NotationConverter::prefixToInfix(std::string inStr){
    std::string pop1;
    std::string pop2;
    std::string toStack;
    std::string reversePre;
    std::string revPre;
    std::string prefixToinfix;
    
    checkValidInp(inStr);

    for(unsigned int i = 0; i < inStr.size(); i++){ //push prefix on stack
        revPre = inStr[i];
        frontinsert(revPre);
    }
    while (head != NULL){ //create reverse string
        reversePre = reversePre + head -> op; 
        removefront();
    }
    for(unsigned int i = 0; i < reversePre.size(); i++){
        if (((reversePre[i] >= 'A' && reversePre[i] <= 'Z') || (reversePre[i] >= 'a' && reversePre[i] <= 'z'))){
            prefixToinfix = reversePre[i];
            frontinsert(prefixToinfix); //push onto stack
        }
        else if (reversePre[i] == MULT ||reversePre[i] == DIV ||reversePre[i] == SUB ||reversePre[i] == ADD){
            pop1 = head -> op + " ";
            removefront();
            pop2 = head -> op;
            removefront();
            toStack = "(" + pop1 + reversePre[i] + " " + pop2 + ")"; 
            frontinsert(toStack); 
        }
    }
    prefixToinfix = head -> op;
    removefront();
    return prefixToinfix;
}

/*********************************************************************************
//                        POSTFIX TO PREFIX
*********************************************************************************/
std::string NotationConverter::postfixToPrefix(std::string inStr){
    std::string postfixtoinfix;
    std::string prefix;

    postfixtoinfix = postfixToInfix(inStr);
    prefix = infixToPrefix(postfixtoinfix); 
    return prefix; 
}


/*********************************************************************************
//                        PREFIX TO POSTFIX
*********************************************************************************/
std::string NotationConverter::prefixToPostfix(std::string inStr){
    std::string preToin; 
    std::string postfix;

    preToin = prefixToInfix(inStr);
    postfix = infixToPostfix(preToin);
    return postfix;
}
