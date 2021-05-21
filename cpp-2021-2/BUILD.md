# Instruction de build pour le projet

Pour compiler le projet, vous aurez besoin de Conan[^conan]. Pour l'installer, il suffit d'utiliser *pip*, le package manager de Python :

```
$ pip install [--user] conan
```

Ensuite, pour compiler le projet, il faut executer les commandes suivantes :

```
$ conan install .. -s compiler.cppstd=20 -s compiler.libcxx=libstdc++11 --build missing
$ cmake ..
$ make
```

Vous pouvez (et devez) utiliser ``make test`` pour lancer vos tests et ``make bench`` pour lancer vos benchs.

En cas de soucis technique, contacter <besteban@lrde.epita.fr>.

[^conan]: <https://conan.io/>