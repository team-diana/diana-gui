TEMPLATE = subdirs

CONFIG += ordered static

SUBDIRS += interface

qutty.file = ./diana-qutty/diana-qutty.pro


interface.depends = diana-qutty

