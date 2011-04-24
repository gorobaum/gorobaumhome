%---------------------------------------------------------------------------------------------------------------------------------------------------%
qSelectCursoA :=
  select codigo1=codigo2 and idministrante=idaluno((oferecimentocurso) product (cursandocurso));

qSelectPessoaA :=
  select id=idministrante ((pessoa) product (qSelectCursoA));

qQuestaoA :=
  project nome (qSelectPessoaA);
%---------------------------------------------------------------------------------------------------------------------------------------------------%
qProjectCursandoB(cod, id) :=
  project codigo2, idaluno (cursandocurso);

qProjectOferecimentoB(cod, id) :=
  project codigo1, idministrante (oferecimentocurso);

qDifference1B(id1) :=
  project id ((qProjectOferecimentoB) difference (qProjectCursandoB));

qDifference2B(id1) :=
  project id ((qProjectCursandoB) difference (qProjectOferecimentoB));

qPessoaIdB(id1) :=
  project id (pessoa);

qAuxB :=
  ((qPessoaIdB) difference ((qDifference1B) union (qDifference2B)));

qQuestaoB :=
  project nome ( select id=id1 ((pessoa) product (qAuxB)));
%---------------------------------------------------------------------------------------------------------------------------------------------------%
qProjectOfe1C :=
  project codigo1, ano1, semestre1, idministrante (oferecimentocurso);

qProjectOfe2C(cod2, ano2, sem2, id2) :=
  project codigo1, ano1, semestre1, idministrante (oferecimentocurso);

qSelectDiffC :=
  select codigo1=cod2 and ( ano1<>ano2 or semestre1<>sem2 or idministrante<>id2) ((qProjectOfe1C) product (qProjectOfe2C));

qQuestaoC :=
  project codigo1 ((project codigo1 (oferecimentocurso)) difference (project codigo1 (qSelectDiffC))) ;
%---------------------------------------------------------------------------------------------------------------------------------------------------%
qProjectOfe1D :=
  project codigo1, ano1, semestre1, idministrante (oferecimentocurso);

qProjectOfe2D(cod2, ano2, sem2, id2) :=
  project codigo1, ano1, semestre1, idministrante (oferecimentocurso);

qSelectDiffD :=
  select codigo1=cod2 and idministrante=id2 and ( ano1<>ano2 or semestre1<>sem2) ((qProjectOfe1C) product (qProjectOfe2C));

qQuestaoD :=
  project codigo1 (qSelectDiffD) ;
%---------------------------------------------------------------------------------------------------------------------------------------------------%
qProjectE :=
  project codigo2, ano2, semestre2, idaluno (cursandocurso);

qSelectE :=
  select codigo2=codigo1 and ano2=ano1 and semestre2=semestre1 and idaluno=idministrante ((qProjectE) product (oferecimentocurso));

qPessoaE :=
  select idaluno=id ((qSelectE) product (pessoa));

qQuestaoE :=
  project nome, codigo1, ano1, semestre1 (qPessoaE);