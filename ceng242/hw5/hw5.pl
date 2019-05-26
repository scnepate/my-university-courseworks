:- module(hw5, [catomic_number/2, ion/2, molecule/2]).
:- [catoms].

sum([], 0).
sum([H|T], SUM) :- sum(T, TS), SUM is H+TS.
catomic_number(NAME, CATOMIC_NUMBER) :-
	catom(NAME, _, _, ELECTRON_LIST),
	sum(ELECTRON_LIST, SUM),
	CATOMIC_NUMBER is SUM.


last([H|[]], H) :- !.
last([_|T], L) :- last(T, L).
ion(NAME, CHARGE) :-
	catom(NAME, _, _, ELECTRON_LIST),
	last(ELECTRON_LIST, L),
	((L =< 4) -> CHARGE is L;CHARGE is L-8).

%sum_of_catomic_numbers([], 0).
sum_of_catomic_numbers([H|[]], MAX) :- catomic_number(H, MAX).	
sum_of_catomic_numbers([H1,H2|T], MAX) :-
	catomic_number(H1, N1), MAX-N1 >= 0,catomic_number(H2, N2), N1 =< N2,
	PASS is MAX-N1, sum_of_catomic_numbers([H2|T], PASS).

total_charge([],0).
total_charge([H|T], TOTAL_CHARGE) :- ion(H, CHARGE), total_charge(T, REST_CHARGE), TOTAL_CHARGE is CHARGE+REST_CHARGE.

molecule(LIST, TOTAL_CATOMIC_NUMBER) :-
	sum_of_catomic_numbers(LIST, TOTAL_CATOMIC_NUMBER),
	total_charge(LIST, TOTAL_CHARGE),
	TOTAL_CHARGE is 0.
molecule([], 0).

%temp([], _).
%temp([H|[]], L) :- H is L.
%temp([H,A|T], L) :- H is L, A is L*2, temp([A|T], L*2).
