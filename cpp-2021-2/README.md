
# SUJET 2 : Une approche bibliothèque au JIT en C++ appliquée au traitement d'images


# Instruction de build pour le projet

Pour compiler le projet, vous aurez besoin de [conan]. Pour l'installer, il suffit d'utiliser *pip*, le package manager de Python :

```
$ pip install [--user] conan
```

# Instruction pour compiler le projet

Pour compiler le projet il vous faudra créer le dossier build à l'aide de cette commande :

```
$ mkdir build
$ cd build
$ conan install .. -s compiler.cppstd=20 -s compiler.libcxx=libstdc++11 --build missing
```

Ensuite, pour compiler le projet, il faut executer les commandes suivantes :

```
$ cmake .. // seulement lors de la première éxécution.
$ make
```

Pour effectuer les tests il suffit de faire ``make test`` et ``make bench`` pour lancer vos benchs.

[conan]: <https://conan.io/>
