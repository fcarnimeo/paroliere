cmake_minimum_required(VERSION 3.13)
project(paroliere C)

set(CMAKE_C_STANDARD 11)

include_directories(paroliere_srv)

add_executable(paroliere
        paroliere_srv/dictionary.c
        paroliere_srv/dictionary.h
        paroliere_srv/includes.h
        paroliere_srv/init.c
        paroliere_srv/init.h
        paroliere_srv/matrix.c
        paroliere_srv/matrix.h
        paroliere_srv/paroliere_srv.c
        paroliere_srv/struct.h
        paroliere_srv/trie.c
        paroliere_srv/trie.h
        paroliere_srv/serverState.c
        paroliere_srv/serverState.h
        paroliere_srv/shutdown.c
        paroliere_srv/shutdown.h
        paroliere_srv/clientHandler.c
        paroliere_srv/clientHandler.h)
