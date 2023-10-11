:- encoding(utf8).


% Task 2: Relational Data

% My representation is (2 mod 4) + 1 = 3 (three)
:- ['three.pl'].
:- ['task1.pl'].
:- ['BasePredicats.pl'].
% Variant 1

% 1.1
% Получаем таблицы групп и ищем средний балл для каждой группы
% ?- getGroupsTable(Group, N, Names).
% ?- getMeanForEachGroup(Group, GroupMean).

getGroup(Group) :- student(Group, _, _).
getGroupsList(GroupList) :- setof(Group, getGroup(Group), GroupList).

getGroupsTable(Group, N, Names) :- getGroupsList(GroupList),
                                member(Group, GroupList),
                                findall(Name, student(Group, Name, _), Names),
                                len(Names, N).

getGroupMarksLists(Group, MarkLists) :- findall(MarkList, student(Group, _, MarkList), MarkLists).

getUnionList([Tail], Tail).
getUnionList([List | ListsTail], UnionList) :-
                                 getUnionList(ListsTail, UnionList1),
                                 append(List, UnionList1, UnionList).


findMarksSum(MarksList, MarksSum) :- findall(Mark, member(grade(_, Mark), MarksList), Marks),
 mySum(Marks, MarksSum).

findGroupMean(Group, GroupMean) :-  getGroupMarksLists(Group, MarksLists),
                                    getUnionList(MarksLists, UMarksList),
                                    findMarksSum(UMarksList, MarksSum),
                                    len(UMarksList, N),
                                    GroupMean is MarksSum / N.

getMeanForEachGroup(Group, GroupMean) :- getGroupsList(GList),
                                    member(Group, GList),
                                    findGroupMean(Group, GroupMean).

% 1.2
% Ищем не сдавших
% ?- getSubjectBacklans(Subject, Backlans).
checkStudent(Group, Student, Subject) :- student(Group, Student, Marks),
                                  member(grade(Subject, 2), Marks). 

getSubjectBacklans(Subject, Backlans) :- subject(SubjectCode, Subject),
                    findall(Backlan, checkStudent(_, Backlan, SubjectCode), Backlans).

% 1.3
% Ищем количество не сдавших
% ?- getGroupBacklansQuantity(Group, BacklansQuantity).
getGroupBacklansQuantity(Group, BacklansQuantity) :-
                    getGroupsList(GList),
                    member(Group, GList),
                    findall(Backlan, checkStudent(Group, Backlan, _), BacklansList1),
                    setof(Backlan, member(Backlan, BacklansList1), BacklansList),
                    len(BacklansList, BacklansQuantity).


