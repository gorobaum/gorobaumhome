% %[o,menino,comeu,o,bolo]
% s(sn(d(o),n(menino)),sv(v(comeu),sn(d(o),n(bolo))))
sentenca --> sintagma_nominal,	sintagma_verbal.

sintagma_nominal --> determinante,nome.

sintagma_verbal --> verbo_transitivo,sintagma_nominal.

determinante --> [o].
determinante --> [a].
determinante --> [um].
determinante --> [uma].

verbo_transitivo --> [comeu].

nome --> [menino].
nome --> [bolo].

