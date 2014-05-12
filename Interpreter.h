/* 
 * File:   Interpreter.h
 * Author: Paulo
 *
 * Created on 12 mai 2014, 11:07
 */

#ifndef INTERPRETER_H
#define	INTERPRETER_H

#ifdef	__cplusplus
extern "C" {
#endif


    void initInterpreter();
    int buildCommande(char c);
    void clearCommande();
    int interpreteCommande();


#ifdef	__cplusplus
}
#endif

#endif	/* INTERPRETER_H */

