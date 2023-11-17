% Place your solution here

:- ['BasePredicats.pl'].

persons([voronov, popugaev, skvorthov, kanareikin, grachev, golubev, chaikin]).
birds([  voron,   popugai,  skvoreth,  kanareika, grach,   golub,   chaika]).

p2b(voronov, voron).
p2b(popugaev, popugai).
p2b(skvorthov, skvoreth).
p2b(kanareikin, kanareika).
p2b(grachev, grach).
p2b(golubev, golub).
p2b(chaikin, chaika).

b2p(Bird, Person) :- p2b(Person, Bird).

formRelations([], [], []).
formRelations([Person | Persons], Birds, [(Person, Bird, IsMarried) | Tail]) :-
	memberWithTail(Bird, Birds, BTail),
	p2b(Person, Bird1), Bird \= Bird1,
	isHeMarried(Person, IsMarried),

	formRelations(Persons, BTail, Tail).


isHeMarried(golubev, false):-!.
isHeMarried(kanareikin, false):-!.
isHeMarried(_, true):-!.

getMoreDarkPBPairs(Relations, LightBirds, Result) :- 
		findall((Person, Bird)
			, (member((Person, Bird, _), Relations)
			, p2b(Person, Bird2)
			, not(member(Bird, LightBirds))
			, member(Bird2, LightBirds)), Result).

check(Relations, LightBirds) :-
	getMoreDarkPBPairs(Relations, LightBirds, Pairs),
	len(Pairs, N),
	3 is N,

	member((voronov, Bird1, _), Relations),
	b2p(Bird1, Person1),
	member((Person1, _, true), Relations),

	member((GrachMaster, grach, true), Relations),
	GrachMaster \= chaikin,

	member((_, voron, false), Relations),

	member((grachev, Bird2, _), Relations),
	b2p(Bird2, Person2),
	member((Person2, kanareika, _), Relations),

	member((voronov, Bird3, _), Relations),
	b2p(Bird3, Person3),
	member((Person4, popugai, _), Relations),
	p2b(Person4, Bird4),
	member((Person3, Bird4, _), Relations).




solve() :- 
	persons(Persons),
	birds(Birds),
	formRelations(Persons, Birds, Relations),
	LBirds = [chaika, golub, popugai, kanareika],
	check(Relations, LBirds),
	member((SMaster, skvoreth, _), Relations),
	write("Skvoreth's master = "), write(SMaster), !.
