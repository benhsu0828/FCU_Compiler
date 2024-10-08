%token DIGIT
%token LPAREN
%token RPAREN
%token PLUS
%token MINUS
%token MULT
%token DIV

%left PLUS
%left MINUS
%left MULT
%left DIV
%start list

%%
list : 
    | list expr
    {
        printf("ANS is: %d\n\n",$2);
    }
    | list expr '\n'
    {
        printf("ANS is: %d\n\n",$2);
    }
    ;
expr : factor PLUS factor
    {
        $$ = $1 + $3;
        printf("%d plus %d equals %d\n",$1,$3,$$);
    }
    | factor MINUS factor
    {
        $$ = $1 - $3;
       printf("%d MINUS %d equals %d\n",$1,$3,$$);
    }
    | expr PLUS factor 
    {
        $$ = $1 + $3;
       printf("%d plus %d equals %d\n",$1,$3,$$);
    }
    | expr MINUS factor 
    {
        $$ = $1 - $3;
       printf("%d MINUS %d equals %d\n",$1,$3,$$);
    }
    | factor
    {
        $$ = $1;
    }
    ;
factor : primary MULT primary
    {
        $$ = $1 * $3;
        printf("%d MULT %d equals %d\n",$1,$3,$$);
    }
    | primary DIV primary
    {
        $$ = $1 / $3;
       printf("%d DIV %d equals %d\n",$1,$3,$$);
    }
    | factor MULT primary
    {
        $$ = $1 * $3;
       printf("%d MULT %d equals %d\n",$1,$3,$$);
    }
    | factor DIV primary
    {
        $$ = $1 / $3;
       printf("%d DIV %d equals %d\n",$1,$3,$$);
    }
    | primary
    {
        $$ = $1;
    }
    ;
primary : LPAREN expr RPAREN
    {
        $$ = $2;
    }
    | DIGIT
    {
        $$ = $1;
    }
    | MINUS DIGIT
    {
        $$ = -$2;
    }
%%
