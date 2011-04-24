%--------------------------------------------------------------------------------------------------------------------------------%
qQuestaoA :=
 select distinct nome
 from oferecimentocurso, cursandocurso, pessoa
 where codigo1=codigo2 and idministrante=idaluno and id=idaluno;
%--------------------------------------------------------------------------------------------------------------------------------%
qProject1B :=
 select distinct codigo1, idministrante
 from oferecimentocurso;

qProject2B :=
 select distinct codigo2, idaluno
 from cursandocurso;

qDiff1B :=
 select idministrante
 from qProject1B, qProject2B
 where codigo1=codigo2 and idaluno<>idministrante;