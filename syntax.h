#include "lexical.h"

void begin(void);
void expr(void);
void term(void);
void factor(void);
void ifsmt(void);
void statement(void);
void loop(void);
void boolexpr(void);
void equality(void);
void comp(void);
void mod(void);
void statement49(void);
// follow the gramer that was used in. if it doesnt work then it will give out a error

//void statement(void);
void begin(void) { //<begin> -> Start <statement> {<statement>} End 
   printf("Enter <Start>\n");
  //lookup(char ch)
  lex();
	/* Parse the first term */
  if(nextToken == Starts){
  lex();
	statement();
     while(nextToken==SEMICOL){
      lex();
    }
    
    if(nextToken == Finish){ //ending point
      printf("pass");
    } 
    while(nextToken==SEMICOL){
      lex();
    }
    while(nextToken!= Finish && nextToken!=EOF){ //check to see if is file is can be repaeated to finish porcessing
      
      statement();
      }
    if(nextToken==Finish){
      printf("pass\n"); //to show it pass
    }
    else{  
      error49();
        
      }
    }
    
  else{
    error49();
  }
  printf("Exit <begin>\n");
  }
  
void expr(void) { //<expr> ->  <term> {(+ | *) <term>} 
	 printf("Enter <expr>\n");
	/* Parse the first term */
 // lex();
	term();
	/* As long as the next token is + or *, get
	 the next token and parse the next term */
	 while (nextToken == ADDITION || nextToken == MULTIPLY) {
     lex();
		 term();
	 }
	 printf("Exit <expr>\n");
}


/* term
 Parses strings in the language generated by the rule:
 <term> -> <comp> {(- | / ) <comp>}
 */
void term(void) {
	 printf("Enter <term>\n");
	/* Parse the first comp */
	 comp();
	/* As long as the next token is - or /, get the
	 next token and parse the next factor */
	 while (nextToken == SUBTRACT || nextToken == DIVIDE ) {
     lex();
		 comp();
	 }
	 printf("Exit <term>\n");
}
// <comp>-> <eqaulity> {(<|>|<=|>=|==) <eqaulity>}
void comp(void){
printf("Enter <comp>\n");
	/* Parse the first factor */
	 equality();
	/* As long as the next token is * or /, get the
	 next token and parse the next factor */
	 while (nextToken == GREATER|| nextToken == LESSEQ || nextToken == GREATEQ || nextToken == LESSER || nextToken==EQUALS)  {
     lex();
		 equality();
	 }
	 printf("Exit <comp>\n");  
}
void equality(void){ //<eqaulity> -> <mod>{(=|!=)<mod> }
printf("Enter <equality>\n");
	/* Parse the first  */
	 mod();
	/* As long as the next token is = or !=, get the
	 next token and parse the next factor */
	 while (nextToken == ASSIGN|| nextToken == NOTEQUAL)  {
     lex();
		 mod();
	 }
	 printf("Exit <equality>\n");  
}
void mod(void){ //<mod>-> <factor> {(%|;)<factor>}
printf("Enter <mod>\n");
	/* Parse the first factor */
	 factor();
	/* As long as the next token is %, get the
	 next token and parse the next mod */
	 while (nextToken == MODULUS  || nextToken== SEMICOL)  {
		 factor();
	 }
	 printf("Exit <mod>\n");  
}


/* factor
 Parses strings in the language generated by the rule:
 <factor> -> id | int_constant | num ident | ( <expr> ) | semicolon
 */
void factor(void) {
	 printf("Enter <factor>\n");
	/* Determine which RHS */
  //lex();
  if(nextToken==DIGITS){
    lex();
    if(nextToken==IDENTI){
      lex();
       if(nextToken==SEMICOL){
        lex(); 
       }else error49();
    }else error49();
  }
	 else if (nextToken == IDENTI || nextToken == INTEGE || nextToken==SEMICOL){
		/* Get the next token */
		 lex();
       }
     
		/* If the RHS is ( <expr> ), call lex to pass over the
		 left parenthesis, call expr, and check for the right
		 parenthesis */
	 else  if (nextToken == LPARPAR) {
     lex();
		 expr();
		 if (nextToken == RPARPAR)
		 	lex();
		 else{
		 	error49();
		 } 
   }
  

		/* It was not an id, an integer literal, or a left
		 parenthesis */
		 else{
		 error49();
	 }
	 printf("Exit <factor>\n");
  
  
  
}
void ifsmt(void) { //<ifsmt>-> con'('<boolexpr>')''{'<statement'}' {<statement}
   printf("Enter <ifsmt>\n");
  //lex();
	 if (nextToken == LPARPAR ) {
     lex();
     boolexpr();
        if(nextToken==RPARPAR){
          lex();
          if(nextToken==LBRACK){
            lex();
            statement();
            if(nextToken==RBRACK){
              lex();
            if(nextToken!= Finish && nextToken!=EOF) {
            statement();
              }
}
            else{
              error49();
            }

          }else error49();
        }else error49();
   }else error49();
  
  } 
		/* Get the next token */
/* <statement>-> <ifsmt> | <loop> | <expr> */  
   void statement(void) {
     printf("Enter <statement>\n");
    // lex();
    if(nextToken==IF_STMT){
      lex();
      ifsmt();
    }
    else if(nextToken == LOOPER){
      lex();
      loop();
    }
   else{
     expr();
   }
 /* while (nextToken!= End && nextToken!=EOF) {
            lex();
            statement2();
   }*/
     printf("Exit <statement>\n");
}
  void loop(void) {
/*  <loop> -> loop(<boolexpr>) '{'
 <statement> '}'
{<statement>} */
    printf("Enter <loop>\n");
    //lex();
    if(nextToken==LPARPAR){
      lex();
      boolexpr();
        if(nextToken == RPARPAR){
        lex();
          if(nextToken==LBRACK){
            lex();
            statement();
            if(nextToken == RBRACK){
            lex();
            if(nextToken!= Finish && nextToken!=EOF) {
            statement();
              }
            }
            else{
            error49();
            }
          }
      }
    }
    else{
      error49();
    }
} 
// <boolexpr>-> identifer (<|>|<=|>=|==|!) int_literal
 void boolexpr(void){
   printf("Enter <boolexpr>\n");
   //lex();
  if(nextToken==IDENTI){
    lex();
    if(nextToken == LESSER ||nextToken==GREATER || nextToken == LESSEQ || nextToken == GREATEQ || nextToken==NOTEQUAL||nextToken==EQUALS ){
      lex();
      if(nextToken==INTEGE){
        lex();
      }else error49();
    }else error49();
  }else error49();
   printf("exit <boolexpr>\n");
} 