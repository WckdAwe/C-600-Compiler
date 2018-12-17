# Επίλυση των Συγκρούσεων
Εδώ έχουμε ένα αρχείο **bison.y** το οποίο θα δημιουργήσει μερικές συγκρούσεις. Πιο συγκεκριμένα θα έχουμε:

    State 165 conflicts: 6 shift/reduce
    State 167 conflicts: 6 shift/reduce
    State 174 conflicts: 6 shift/reduce
    State 241 conflicts: 6 shift/reduce
    State 242 conflicts: 6 shift/reduce
    State 243 conflicts: 6 shift/reduce
    State 244 conflicts: 6 shift/reduce
    State 245 conflicts: 6 shift/reduce
    State 246 conflicts: 6 shift/reduce
    State 251 conflicts: 1 shift/reduce

Μετά από έλεγχο του αρχείου **bison.output** μπορούμε να δούμε ότι τα conflicts δημιουργούνται από τον κανόνα της γραμματικής **expression** και το **ξεκρέμαστο IF/ELSE**.

Επιλύουμε το πρόβλημα τις συγκρούσεις στις πράξεις εφαρμόζοντας τους κανόνες πράξεων, βάση του Πίνακα "Order of Operations" που υπάρχει και στο [Wikipedia](https://en.wikipedia.org/wiki/Order_of_operations). 

Έτσι καταλήγουμε στο να προσθέσουμε τον εξής κώδικα για την επίλυση του κανόνα **expression**:

    %left T_COMMA
    %right T_ASSIGN 
    %left T_OROP
    %left T_ANDOP
    %left T_EQUOP
    %left T_RELOP
    %left T_ADDOP
    %left T_MULOP 
    %left T_NOTOP T_REFER T_SIZEOP T_INCDEC 
    %left T_LPAREN T_RPAREN T_LBRACK T_RBRACK T_DOT T_METH
Για το **ξεκρέμαστο IF/ELSE** τροποποιούμε τον κανόνα στο ακόλουθο:

    %nonassoc LOWER_THAN_ELSE
    %nonassoc T_ELSE

και
	
    if_tail:  T_ELSE statement
            | %empty %prec LOWER_THAN_ELSE  {}
Τέλος επιλύουμε και το πρόβλημα με το αρνητικό πρόσημο γνωστό **unary minus** προσθέτοντας τα ακόλουθα:

    %left T_NOTOP T_REFER T_SIZEOP T_INCDEC **UMINUS**
και

    expression:  expression T_OROP expression
               | expression T_ANDOP expression
               | expression T_EQUOP expression
               | expression T_RELOP expression
               | expression T_ADDOP expression
               | expression T_MULOP expression
               | T_NOTOP expression
               | T_ADDOP expression **%prec UMINUS**
               | T_SIZEOP expression
               | T_INCDEC variable
               | variable T_INCDEC
               | variable
               | variable T_LPAREN expression_list T_RPAREN
               | T_LENGTH T_LPAREN general_expression T_RPAREN
               | T_NEW T_LPAREN general_expression T_RPAREN
               | constant
               | T_LPAREN general_expression T_RPAREN
               | T_LPAREN standard_type T_RPAREN
               | listexpression
               ;

