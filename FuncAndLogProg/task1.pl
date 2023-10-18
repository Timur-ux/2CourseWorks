:- ['BasePredicats.pl'].

% 1 task = (2 mod 19) + 1 = 3 variant;
% 2 task = (2 + 5) mod 20 + 1 = 8 variant

% TASK 1

% Базовые предикаты
baseRemoveNLast(List, N, Result) :- append(Result, Tail, List), len(Tail, N).

% Мои предикаты

myLen(List, Result) :- myLenInner(List, 0, Result).
myLenInner([], N, N).
myLenInner([_|Tail], N, Result) :- N1 is N + 1, myLenInner(Tail, N1, Result).

myRemoveNLast([Head | Tail], N, [Head]) :- myLen(Tail, N).
myRemoveNLast([Head | Tail], N, [Head | Result]) :- myRemoveNLast(Tail, N, Result).

% TASK 2

% Базовые предикаты
mySum([], 0).
mySum([H|T], Result) :- mySum(T, Result1), Result is H + Result1.

baseMean(List, Result) :- mySum(List, S), len(List, N), Result is S / N.

% Мои предикаты

% Т.к. среди базовых нет предиката суммы, данный предикат также считается моим

myMean(List, Result) :- mySum(List, S), myLen(List, N), Result is S / N.