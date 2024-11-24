/***************************************************************************
 *   exN.cpp                                  Version 20230620.225755      *
 *                                                                         *
 *   Programa Principal                                                    *
 *   Copyright (C) 2023         by Ruben Carlo Benante                     *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License.               *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 *   To contact the author, please write to:                               *
 *   Ruben Carlo Benante                                                   *
 *   Email: rcb@beco.cc                                                    *
 *   Webpage: http://www.beco.cc                                           *
 *   Phone: +55 (81) 3184-7555                                             *
 ***************************************************************************/

/*
 * Instrucoes para compilar:
 *   $ make exN.out
 * Leia mais detalhes no arquivo INSTALL
 */

/* ---------------------------------------------------------------------- */
/* includes */

#include "ui_mainmenu.h"
#include "mainwin.hpp"
#include "loginwindow.h"

/* ---------------------------------------------------------------------- */
/* definitions */

/* limits */
#define SBUFF 256 /* string buffer */

/* ---------------------------------------------------------------------- */
/* This function does ...
 * It receives as input ...
 * It returns ...
 */
int main(int argc, char **argv)
{
    /* local declarations */
    int i; /* general index */
    char s[SBUFF]; /* a string to hold ... */

    /* Q_INIT_RESOURCE(x); */

    QApplication app(argc, argv);
    LoginWindow win;
    MainWindow w;



    win.show();

    /* code */

    /* ...and we are done */
    return app.exec();
}

/* add more functions here */

/* ---------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : CPP config - Vim modeline */
/* Template by Dr. Beco <rcb at beco dot cc> Version 20220718.172615      */

