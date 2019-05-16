# Tema2 SD 2019, DNS Hierarchy
# 311CC Cretan Gheorghe-Cristian

For the DNS Hierarchy implementation and given the restraints
(the nodes given in random order), I thought that using a forest of trees 
in the beginning would be a lot more easier.
The idea is that in the first place I create a tree for every node, then
while I read the nodes I just add them to their parents as a child and set the
corresponding parent pointer. After that I unite all the forest in one single
tree that would be used to solve the given queries.
When I unite all the forest, I loop through all the nodes and unite the
respective nodes with their parents.
* Task 1
For this task I just recursively printed every node and it's children.
* Task 2
For this task the idea was that find all the leaves then just go up the tree
until you are in root to update the addresses.
* Task 3
For this task I just started in the queried node and went up the tree
until I find the address that I have to resolve while caching the address on
every node that I traversed.
* Bonus
Basically just deleting a node from the tree and appending all of it's children
to the deleted node's parent.

Pentru implementarea arhivei DNS si luand in considerare constriganderile
(nodurile date in oridine aleatoare), am considerat ca folosind o padure ar fi
benefic.
Ideea este ca, la inceput, atribui fiecarui nod un arbore propriu,
apoi pe masura ce citesc nodurile si parintii acestora, pot pur si simplu
sa adaug la respectivul nod (parinte), nodul copil dat, impreuna cu toate
adresele citite. Dupa terminarea citirii pot sa unesc toata padurea intr-un
singur arbore pentru a-l folosi mai departe in rezolvarea cerintelor.
Cand fac unirea padurii, trec prin toate nodurile si pur si simplu unesc nodul
radacina din arborele curent cu parintele acestuia.

* Cerinta 1
Pentru aceasta cerinta am printat recursiv fiecare nod impreuna cu copii acestuia.
* Cerinta 2
Pentru aceasta cerinta ideea a fost: gaseste toate frunzele dupa care mergi
in sus pe arbore in timp ce pui adresele copilului la parinte.
* Cerinta 3
Pentru aceasta cerinta am inceput din nodul care are de rezolvat o adresa
de unde am mers din nou in sus din parinte in parinte pana cand am gasit un
nod care poate rezolva adresa respectiva, intre timp tinand minte adresa in
fiecare nod.
* Bonus
Practic trebuia doar sa sterg un nod si sa adaug toti copiii acestuia,
parintelui respectiv.

# Feedback pentru tema si observatii:
Ideea temei a fost OK, task-urile in schimb au fost ad-hoc. Nu prea ai avut
nevoie sa gandesti la ele. Adevarata greutate a temeia fost modul cum iti
defineai structura. In rest, nu am ce sa zic, o aplicatie buna a arborilor
in raport cu ideea temei, totusi e o tema cu potential, putea fi
mult mai interesanta decat este acum, dar asta este doar o opinie personala.

De asemenea, as vrea sa adaug niste observatii la coding-style, deoarece
din cauza acestui aspect am fost depunctat in tema trecuta, desi credeam ca
tema mea este destul de ok, am inteles ideea cu modularizarea, dar consider ca
unele lucruri depind si de preferinta si pana la urma ideea este sa fi
consistent in codul tau. O sa las niste articole despre consecventa condului
si despre preferinte si dependenta "frumusetii" de consistenta ([1] [2]).

Sper ca aceasta tema se ridica la standardele de coding style. Am incercat cat
mai mult sa evit liniile de peste 80 de caractere dar cele care sunt, sunt din
cauza tab-urilor, acolada o sa continui sa o pun jos, deoarece
aste e preferinta mea personala.

[1] https://softwareengineering.stackexchange.com/q/190649
[2] https://softwareengineering.stackexchange.com/q/2715