% Users(BasePredicats.pl) для подключения данного файла.

len([], 0).
len([_|T], N) :- len(T, N1), N is N1 + 1.

member(X, [X|_]).
member(X, [_|T]) :- member(X, T).

append([], Result, Result).
append([Current|TailFrom], ListFrom2, [Current|TailTo]) :- append(TailFrom, ListFrom2, TailTo).

remove(X, [X|T], T).
remove(X, [Head | Tail], [Head | ResultTail]) :- remove(X, Tail, ResultTail).

removeList([], List, List) :- !.
removeList([ElemToRemove| TailToRemove], List, Result) :-
	remove(ElemToRemove, List, Temp),
	removeList(TailToRemove, Temp, Result).

getNLast(List, Result, N) :- append(_, Result, List), len(Result, N).

sublist(List1, List2, Result) :- append(HeadL1, _, List1),
                                 append(HeadL2, _, List2),
                                 append(_, Result, HeadL1),
                                 append(_, Result, HeadL2),
                                 Result \== [].


permute([],[]).
permute(List, [Head | Tail]) :- remove(Head, List, Result), permute(Result, Tail).

insert(nil, X, bt(nil, X, nil)).
insert(bt(LT, Root, RT), X, bt(LTNew, Root, RT)) :- X < Root, insert(LT, X, LTNew).
insert(bt(LT, Root, RT), X, bt(LT, Root, RTNew)) :- X >= Root, insert(RT, X, RTNew).

listToTree([], nil).
listToTree([Head|Tail], Tree) :- listToTree(Tail, TreeTemp), insert(TreeTemp, Head, Tree).

treeToList(nil, []).
treeToList(bt(LT, Root, RT), List) :- treeToList(LT, ListLeft), treeToList(RT, ListRight), append(ListLeft, [Root | ListRight], List).

mySort(List, Result) :- listToTree(List, Tree), treeToList(Tree, Result).


memberWithTail(Elem, [Elem | Tail], Tail).
memberWithTail(Elem, [ListHead | ListTail], Tail) :- memberWithTailInner(ListTail, ListHead, Elem, Tail).

memberWithTailInner(Tail, Elem, Elem, Tail).
memberWithTailInner([ListTailHead|ListTailTail], Head, Elem, [Head|TailTail]) :- memberWithTailInner(ListTailTail, ListTailHead, Elem, TailTail).
