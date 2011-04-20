/*
 *      �������� RED.
 *
 *      $Header: r.file.c,v 4.20 90/05/22 23:22:01 alex Exp $
 *      $Log:   r.file.c,v $
 * Revision 4.20  90/05/22  23:22:01  alex
 * First rev. red 4.2
 * 
 * Revision 4.10  90/02/05  19:52:24  alex
 * Base revision 4.1
 * 
 * Revision 4.1  88/03/31  22:02:42  alex
 * ������ 4.1 - ������� �� UTEC, ��
 * 
 * Revision 3.1.2.2  87/06/23  18:51:04  alex
 * wYNESENA PEREMENNAQ lread1 I \TO OTLAVENO
 * 
 * Revision 3.1.2.1  87/06/19  17:00:09  alex
 * Start revision for red/4
 * 
 * Revision 3.5  87/06/05  23:50:24  alex
 * �������� roll ��� ���������� � sr/sf � �����������
 *  ��������� � ������ -t + ������ ������
 * 
 * Revision 3.4  86/09/19  19:52:46  alex
 * ������ ��� ��-1700
 * 
 * Revision 3.3  86/08/04  20:51:42  alex
 * Bepqh dk LMNQ/DELNQ 2
 * 
 * Revision 3.2  86/07/24  00:24:13  alex
 * ��'������� ������ ������� ��� �� � ��
 * 
 * Revision 3.1.1.3  86/06/16  22:17:57  alex
 * ������ ������ � �������� ������ (���� �������)
 * 
 * Revision 3.1.1.1  86/06/05  00:04:36  alex
 * ��������_��_������
 * 
 * Revision 3.1  86/04/20  23:41:27  alex
 * ������� ������ ��� ��.
 * 
 * Revision 3.1  86/04/20  23:41:27  alex
 * *** empty log message ***
 * 
 *
 * r.file.c - ������ � �������.
 *
 */

#include "r.defs.h"
#include <signal.h>

/*
 * savefile(file,n) -
 * ������ ����� �� ������ n � ���� "file"
 * ���� file �� �����, ������������ ���� ������ ���
 * openfnames[n];
 * ���� ���� �� ������������, ���������� �������� ��� � "."
 */
savefile(file,n)
char *file;
int n;
{
    register char *f1;
    char *f0, *f2;
    register int i, j;
    int lread1;
    int newf,nowrbak=0;
    /* ��� ���������� */
    putline(1);
    if (file) {
        f0=file;
    } 
    else {
        f0=openfnames[n]; 
        nowrbak=1;
    }
    for (f1=f2=f0; *f1; f1++) if (*f1 == '/') f2 = f1;
    if (f2 > f0)
    {
        *f2 = '\0';
        i = open(f0,0);
        *f2 = '/';
    }
    else i = open (".",0);
    if (i < 0)
    {
        error (DIAG("Directory does not exist.","���������� �� ����������."));
        return(0);
    }
    j = checkpriv(i);
    close (i);
    if (j != 2)
    {
        if (file)
        {
            error (DIAG("Can't write in specified directory","������ � ���������� ���������"));
            return(0);
        }
        if (f2 > f0)
        {
            telluser(DIAG("Hit <save> to use '.'","������� <save> ����� ������������ '.'"),0);
            nowrbak=0;
#ifdef DEMOSES
            editwind((struct viewport *)0,(int (*)())0,0);
            newedit = 1;
#endif /* DEMOSES */
            lread1=readch();
            if (lread1 != CCSAVEFILE) return(-1);
            if ((i = open(".",0)) < 0)
            {
                error (DIAG("Directory '.' does not exist!","���������� '.' �� ����������!"));
                return(0);
            }
            j = checkpriv(i);
            close (i);
            if (j != 2)
            {
                error (DIAG("Can't write in '.'","������ � '.' ����������"));
                return(0);
            }
            f0 = f2 +1;/* points to file name */
        }
        else
        {
            error (DIAG("Can't write in '.'","������ � '.' ����������"));
            return(0);
        }
    }
    /* ��������� � ������ ����� f0 */
    f1 = append (f0,SUFFBAK);
    if (nowrbak && !movebak[n]) {
        nowrbak=0; 
        movebak[n]=1;
    }
    if (!nowrbak)
    {   
        unlink(f1);
        link (f0,f1);
    }
    unlink (f0);
    if ((newf = creat(f0,getpriv(n))) < 0)
    {
        error (DIAG("Creat failed!","������ ��������!"));
        return(0);
    }
    /*      chown(f0,userid);       */
    /* ���������� ������. */
    telluser(DIAG("save: ","���: "),0);
    telluser(f0,6);
    dumpcbuf(1);
    return (fsdwrite(openfsds[n],077777,newf) == -1 ? 0 : 1);
}

/*
 * fsdwrite(f,nl,newf) -
 * ������ �� ������� ���������� f � ���� "newf"
 * ���� nl # 0  - ���������� ������ nl ����� ���
 * -nl ������� ������ (nl ������������ � ������
 * ������� "exec".
 * ����� - ����� ���������� �����, ��� -1, ���� ������.
 */
fsdwrite(ff,nl,newf)
struct fsd *ff;
int nl, newf;
{
    register struct fsd *f;
    register char *c;
    register int i;
    int j,k,bflag,tlines;
    if (lcline < LBUFFER) excline(LBUFFER);
    f = ff;
    bflag = 1;
    tlines = 0;
    while (f->fsdfile && nl)
    {
        if (f->fsdfile > 0)
        {
            i = 0;
            c = &f->fsdbytes;
            for (j=f->fsdnlines; j; j--)
            {
                if (nl < 0) {
                    /* ��������� ������� ������ ����� */
                    if (bflag && *c != 1) bflag = 0;
                    else if (bflag == 0 && *c == 1) {
                        bflag = 1;
                        if (++nl == 0) break;
                    }
                }
                if (*c&0200) i += 128 * (*c++&0177);
                i += *c++;
                ++tlines;
                /* ��������� ������� ����� */
                if (nl > 0 && --nl == 0) break;
            }
            seek(f->fsdfile,f->seekhigh,3);
            seek(f->fsdfile,f->seeklow,1);
            while (i)
            {
                j = i < LBUFFER ? i : LBUFFER;
                read(f->fsdfile,cline,j);
                if (write(newf,cline,j) < 0)
                {
#ifdef SIGNOSPC
                    if ( werrflag )
                    error(DIAG("WRITE ERROR-NO SPACE","O����a �a��c�:�e� �ec�a"));
                    else
                    error(DIAG("DANGER -- WRITE ERROR","B���a��e:o����� ������"));
                    werrflag = 0;
#else
                    error(DIAG("DANGER -- WRITE ERROR","B���a��e:o����� ������"));
#endif
                    close(newf);
                    return(-1);
                }
                i -= j;
            }
        }
        else
        {
            j = f->fsdnlines;
            if (nl < 0) {
                if (bflag == 0 && ++nl == 0) j = 0;
                bflag = 1;
            }
            else {  
                if (j > nl) j = nl;
                nl -= j;
            }
            k = j;
            while (k) cline[--k] = NEWLINE;
            if (j && write(newf,cline,j) < 0)
            {
                error(DIAG("DANGER -- WRITE ERROR","��������: ������ ������."));
                close(newf);
                return(-1);
            }
            tlines += j;
        }
        f = f->fwdptr;
    }
    close(newf);
    return tlines;
}

/*
 * editfile(file,line,col,mkflg,puflg) -
 * ������� ���� file ��� ��������������, ������� �� ������
 * line � ������� col.
 * ���� ����������� � ������� ����.
 * ���� ����� ���, � mkflg ����� 1, �� �������������
 * ���������� ������� ����.
 * ��� ������ -1, ���� ���� �� ������� � �� �������.
 * ���� putflg ����� 1, ���� ��� �� ��������� � ����.
 */
editfile(file,line,col,mkflg,puflg)
char *file;
int line, col, mkflg, puflg;
{
    int i,j;
    register int fn;
    register char *c,*d;
    int lread1;
    int linecursor;
    /* ������� ��� ��������� */
    putline(1);
    fn = -1;
    for (i=0; i<MAXFILES;++i) if (openfnames[i] != 0)
    {
        c = file;
        d = openfnames[i];
        while (*(c++) == *d) if (*(d++) == 0)
        {
            fn = i;
            break;
        }
    }
    if (fn < 0)
    {
        fn = open(file,0);  /* ���� ����������? */
        if (fn >= 0)
        {
            if (fn >= MAXFILES)
            {
                error(DIAG("Too many files -- editor limit!","������� ����� ������"));
                close(fn);
                return(0);
            }
            if ((j = checkpriv(fn)) == 0)
            {
                error(DIAG("File read protected.","���� ������� �� ������."));
                close(fn);
                return(0);
            }
            openwrite[fn] = (j == 2 ? 1 : 0);
            telluser(DIAG("Use: ","���: "),0);

            telluser(file,5);
        }
        else if (mkflg)
        {
#ifndef DEMOSES
            telluser(DIAG("Create(y/n)?: ","�������(y/n)?: "),0);
            telluser(file,DIAG(15,15));
#else /* +DEMOSES */
            telluser(DIAG("hit <use> (ctrl-d) to make: ","������� <���>, ����� �������: "),0);
            telluser(file,DIAG(28,30));
            editwind((struct viewport *)0,(int (*)())0,0);
            newedit = 1;
#endif /* +DEMOSES */
            lread1=readch();
            if (lread1 != CCSETFILE&&lread1 != 'Y' &&lread1 != 'y') return(-1);
            /* ������� ���������� */
            for (c=d=file; *c; c++)  if (*c == '/') d = c;
            if (d > file)
            {
                *d = '\0';
                i = open(file,0);
            }
            else i = open(".",0);
            if (i < 0)
            {
                error(DIAG("Specified directory does not exist.","���������� �� ����������"));
                return(0);
            }
            if (checkpriv(i) != 2)
            {
                error(DIAG("Can't write in:","�� ���� �������� �:"));
                telluser (file,21);
                return(0);
            }
            close(i);
            if (d > file) *d = '/';
            /* ������� ���� */
            fn = creat(file,FILEMODE); 
            close(fn);
            if ((fn = open(file,0)) < 0)
            {
                error(DIAG("Create failed!","������ �������� �����."));
                return(0);
            }
            if (fn >= MAXFILES)
            {
                close(fn);
                error(DIAG("Too many files -- Editor limit!","������� ����� ������."));
                return(0);
            }
            openwrite[fn] = 1;
            chown(file,userid,groupid);
        }
        else return (-1);
        paraml = 0;   /* so its kept around */
        openfnames[fn] = file;
    }
    /* ����������� �����, ��� ��� ����� ������ �������� */
    dumpcbuf(1);
    switchwksp(1);
    if (openfsds[fn] == (struct fsd *)0)
        openfsds[fn] = file2fsd(fn);
    curwksp->curfsd = openfsds[fn];
    curfile = curwksp->wfile = fn;
    curwksp->curlno = curwksp->curflno = 0;
    line -= defplline;
    linecursor = defplline;
    if ( line < 0 ) {
        linecursor += line;
        line = 0;
    }
    curwksp->ulhclno = line;
    curwksp->ulhccno = col;
    if (puflg)
    {
        out_lines(0,-1);
        poscursor(0,linecursor);
    }
    return(1);
}


/*
 * endit() -
 * ��������� ������ � �������� ���
 * ����� = 0, ���� ��� ������ ���� ������
 */
endit()
{
    register int i, ko = 1;
    putline(1);
    for (i = 0; i < MAXFILES; i++)
        if (openfsds[i] && openwrite[i] == EDITED)
            if (savefile(NULL,i) == 0) ko = 0;
    return(ko);
}
