$$
\begin{align}
    [\text{Prog}] &\to [\text{Stmt}]^* \\
    [\text{Stmt}] &\to
    \begin{cases}
        \text{exit}([\text{Expr}]); \\
        \text{let}\space\text{[VarType]}\space\text{ident} = [\text{Expr}]; \\
        \text{ident} = \text{[Expr]}; \\
        \text{if} ([\text{BoolExpr}])[\text{Scope}]\text{[IfPred]} \\
        \text{while} ([\text{BoolExpr}])[\text{Scope}] \\
        [\text{Scope}] \\
        \text{return}([\text{Expr}]); \\
        \text{function}\space\text{ident}\space\text([\text{DeclParam}])[\text{Scope}] \\
        \text{ident}([\text{CallParam}]); 
    \end{cases} \\
    \text{[VarType]} &\to 
    \begin{cases}
        \text{int} \\
        \text{char} \\
    \end{cases} \\
    \text{[DeclParam]} &\to 
    \begin{cases}
        [\text{VarType}]\space\text{ident} \\
        [\text{VarType}]\space\text{ident},\space\text{[DeclParam]} \\
    \end{cases} \\
    \text{[CallParam]} &\to 
    \begin{cases}
        [\text{Expr}] \\
        [\text{Expr}],\space\text{[CallParam]} \\
    \end{cases} \\
    \text{[Scope]} &\to \{[\text{Stmt}]^*\} \\
    \text{[IfPred]} &\to 
    \begin{cases}
        \text{elif}(\text{[Expr]})\text{[Scope]}\text{[IfPred]} \\
        \text{else}\text{[Scope]} \\
        \epsilon
    \end{cases} \\
    [\text{Expr}] &\to
    \begin{cases}
        [\text{Term}] \\
        [\text{BinExpr}] \\
    \end{cases} \\
    [\text{BinExpr}] &\to
    \begin{cases}
        [\text{Expr}] * [\text{Expr}] & \text{prec} = 1 \\
        [\text{Expr}] / [\text{Expr}] & \text{prec} = 1 \\
        [\text{Expr}] + [\text{Expr}] & \text{prec} = 0 \\
        [\text{Expr}] - [\text{Expr}] & \text{prec} = 0 \\
    \end{cases} \\ 
    [\text{BoolExpr}] &\to
    \begin{cases}
        [\text{Expr}] > [\text{Expr}] \\
        [\text{Expr}] < [\text{Expr}] \\
        [\text{Expr}] >= [\text{Expr}] \\
        [\text{Expr}] >= [\text{Expr}] \\
        [\text{Expr}] == [\text{Expr}] \\
        [\text{Expr}] != [\text{Expr}] \\
        \text{true} \\
        \text{false} \\
    \end{cases} \\ 
    [\text{Term}] &\to
    \begin{cases}
        \text{int\_lit} \\
        \text{char\_lit} \\
        \text{ident} \\
        ([\text{Expr}])
    \end{cases}
\end{align}
$$
