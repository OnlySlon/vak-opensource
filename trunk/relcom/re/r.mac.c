/*
 *      �������� RED.
 *
 *      $Header: r.mac.c,v 4.20 90/05/22 23:22:08 alex Exp $
 *      $Log:   r.mac.c,v $
 * Revision 4.20  90/05/22  23:22:08  alex
 * First rev. red 4.2
 * 
 * Revision 4.10  90/02/05  19:52:27  alex
 * Base revision 4.1
 * 
 * Revision 4.1  88/03/31  22:03:40  alex
 * ������ 4.1 - ������� �� UTEC, ��
 * 
 * Revision 3.1.2.2  87/06/23  18:51:42  alex
 * wYNESENA PEREMENNAQ lread1 I \TO OTLAVENO
 * 
 * Revision 3.1.2.1  87/06/19  17:00:53  alex
 * Start revision for red/4
 * 
 * Revision 3.5  87/06/05  23:50:50  alex
 * �������� roll ��� ���������� � sr/sf � �����������
 *  ��������� � ������ -t + ������ ������
 * 
 * Revision 3.4  86/09/19  19:54:15  alex
 * ������ ��� ��-1700
 * 
 * Revision 3.3  86/08/04  20:52:20  alex
 * Bepqh dk LMNQ/DELNQ 2
 * 
 * Revision 3.2  86/07/24  19:12:03  alex
 * ��'������� ������ ������� ��� �� � ��
 * 
 * Revision 3.1.1.2  86/06/05  18:53:55  alex
 * ��������_��_������
 * 
 * Revision 3.1.1.1  86/06/05  00:05:14  alex
 * ��������_��_������
 * 
 * Revision 3.1  86/04/20  23:42:10  alex
 * ������� ������ ��� ��.
 * 
 * Revision 3.1  86/04/20  23:42:10  alex
 * *** empty log message ***
 * 
 * Revision 1.4  86/04/13  22:01:27  alex
 */


/* ���� �������� ���������, ����������� ����� �����������
 *  ��������� "RED", ��������� � ����������������
 *
 * ���� ��������
 TAG - ����� � �����
 BUF - ����� �������
 MAC - �����=�������
 *
 * � ������-�� ��� ��� ������� ��������� ���������
*/

#include "r.defs.h"

#define MTAG 1
#define MBUF 2
#define MMAC 3

struct tag {int line, col, nfile;};
#define MSBUF SSAVEBUF
#define MSTAG sizeof(struct tag)
#define MSMAC sizeof(char *)

#define LMAC ('z'-'a'+11)
/* ����� ����� */
static char Mnames[]="abcdefghijklmnoqprstuvwxyz0123456789";
int csrsw; /* ��� ����� ������� �� ������ */
union macro {struct savebuf mbuf; struct tag mtag; char *mstring;}
                *mtaba[LMAC], *mmtaba[LMAC];
char mtabt[LMAC];

/*
 * union macro *mname(name,typ,l)
 * ������� ������ ��������� �� �����
 * ���� l=0, �� ���� � ��������� ���,
 * ����� ������� ����� ���������
 */
union macro *mname(name,typ,l)
register char *name;
int typ,l;
{
    register int i;char cname;
    register union macro **pm;
    cname = *name;
    if ( cname >= '0' && cname <= '9' ) cname = 'z'+ (cname-'0') +1;
    cname = (cname|040) & 0177;
    i= cname -'a';
    if(i >= LMAC || i < 0 || (*(name+1) != 0))
    {
        error(DIAG("ill.macro name","�����.��� �����"));
        goto err;
    }
    pm = (typ != MMAC? &(mtaba[i]): &(mmtaba[i]));
    if(l) {
        if(*pm) {
            if (typ == MMAC && (*pm)->mstring ) zFree((*pm)->mstring);
            zFree((char *)(*pm));
        }
        if ( typ != MMAC ) mtabt[i]=typ;
        *pm =(union macro *)salloc(l);
        goto retn;
    }
    if( typ == MMAC && !(*pm) ) {
        error( DIAG("undefined","������������"));
        goto err;
    }
    if( typ != MMAC && mtabt[i] != typ) {
        error( mtabt[i]?DIAG("ill.macro type","����.��� �����"):DIAG("undefined","������������"));
        goto err;
    }
retn:
    return(*pm);
err:
    return(0);
}

/*
 * msrbuf( sbuf, name,op)
 * ������� ���������� � ������ ����� �������
 * op=1 - ������, 0 - ���������
 * ����� 1, ���� ������, ����� 0
 */
msrbuf( sbuf, name,op)
register struct savebuf *sbuf;
register char *name;
int op;
{
    register union macro *m;
    if ((m=mname(name,MBUF,(op?0:MSBUF))))
        {
        if(op) *sbuf = m->mbuf; else m->mbuf = *sbuf;
        return(1);
    }
    return(0);
}

/*
 * msvtag(name) -
 * ������� ���������� ������� ��������� ������� � ����� ��� ������ name.
 * �� ������ � ���, ��� tag (�����) �� ������� � ������ ������ �
 * ������������ ��� �������������� ���������� ����� �����
 */
msvtag(name)
register char *name;
{
        register union macro *m; register struct workspace *cws;
        cws = curwksp;
        if( !(m=mname(name,MTAG,MSTAG)) ) return(0);
        m->mtag.line = cursorline + cws->ulhclno;
        m->mtag.col  = cursorcol  + cws->ulhccno;
        m->mtag.nfile= cws->wfile;
        return(1);
}

/*
 * mgotag(name) -
 * ������� mgotag ������ ��� ��������� ������� ������� � �����������
 * �����. cgoto �������� ����� ��� ��� � ��� ���������� ������ �������
 */
mgotag(name)
char *name;
{
    register int i;
    int fnew=0;
    register union macro *m,*m1;
    if( !(m=mname(name,MTAG,0))) return(0);
    /* ������ �������� �������� �� ����� 1 */
    /* ���� ������� ��������, �� ���� �� ����� 2, ����� ������� ����� 2 */
    if ( name[0] == '1' ) {
      if ( curwksp->wfile == m->mtag.nfile
           && ABS_LIN(cursorline) == m->mtag.line
           && ABS_COL(cursorcol)  == m->mtag.col
           && (m1 = mname("2",MTAG,0) ) ) m = m1;
      else
            msvtag("2");
    }
    if (curwksp->wfile != (i=m->mtag.nfile))
    {
        editfile(openfnames[i],0,0,0,0);
        fnew=1;
    }
    cgoto(m->mtag.line, m->mtag.col, -1, fnew);
/*    csrsw = 1;      */
    return(1);
}

/*
 * mdeftag(name)
 * ������� mdeftag ������������ ���������, ����������� �������
 *  ����� ������� ���������� ������� � ������ "name". ��� ���������:
 *      paramtype = -2
 *      paramc1   =    ������������� ����� "name"
 *      paramr1   =           -- // --
 */
mdeftag(name)
char *name;
{
    register union macro *m;
    if( !(m=mname(name,MTAG,0))) return(0);
    return(set_param(m->mtag.nfile,m->mtag.line,m->mtag.col));
}

set_param(nfile,line,col)
int nfile,line,col;
{
    register struct workspace *cws; 
    int cl,ln,f=0;
    cws = curwksp;
    if(nfile != cws->wfile) {
        error(DIAG("another file","������ ����"));
        return(0);
    }
    paramtype= -2;
    paramr1 = line;
    paramc1 = col ;
    paramr0 += cws -> ulhclno;
    paramc0 += cws -> ulhccno;
    if( paramr0 > paramr1) {
        f++;
        ln = paramr1;
        paramr1 = paramr0; 
        paramr0 = ln;
    }
    else ln = paramr0;
    if( paramc0 > paramc1) {
        f++;
        cl = paramc1;
        paramc1 = paramc0; 
        paramc0 = cl;
    }
    else cl = paramc0;
    if( f ){
        cgoto(ln,cl,-1,0);
    }
    paramr0 -= cws -> ulhclno;
    paramr1 -= cws -> ulhclno;
    paramc0 -= cws -> ulhccno;
    paramc1 -= cws -> ulhccno;
    if (paramr1 == paramr0)
        telluser(DIAG("**:columns defined by tag","***����� ������ ������� ������***"),0);
    else if(paramc1 == paramc0)
        telluser(DIAG("**:lines defined by tag","***:������ ������� ������"),0);
    else telluser(DIAG("**:square defined by tag","**:������������� ������ ������"),0);
    return(1);
}

/*
 * defmac(name)
 * ��������� ����������� ����� - ������������������,
 */
defmac(name)
char *name;
{
    register union macro *m;
    if(!(m = mname(name,MMAC,MSMAC))) return(0);
    param(1);
    if(paramtype == 1 && paramv)
        {    
        m->mstring = paramv; 
        paraml = 0; paramv=NULL;
        return(1);
    }               
    return(0);
}

/*
 * NewMacro(name, macro)
 * �������� ����� "macro" ��� ������ name
 * macro ������ ��� ���� ��������� � ������
 * ����� - 0 - �����, ���� ��� ������� ��� ������ ����� �����
 */
NewMacro(name, macro)
char *name, *macro;
{
    register union macro *m;
    int i;
    /* �������� ����� �� ����� */
    i = name[0];
    if ( i >= '0' && i <= '9' ) i = i - '0' + ('z'+1);
    i = i - 'a' + (CCMAC+1);
    if(!(m = mname(name,MMAC,MSMAC))) return(0);
    m->mstring = macro;
    return(i);
}

char Mac_info[3];
/*
 * char *rmacl(isy)
 * �������� ����� = ������������������ ��� 0;
 * ��� ������������ ��� ���� ������ � ����� isy - 0200 + 'a'
 */
char *rmacl(isy)
int isy;
{
        char nm[2];
        register union macro *m;
        nm[0]=isy - (CCMAC+1) + 'a';
        nm[1] =0;
        if (!(m=mname(nm,MMAC,0))) return(0);
        return(m->mstring);
}

#define LKEY 20 /* ����. ����� ��������, ������������ ����� �������� */
/*
 * defkey()
 * ������� ������ ��� ����������� ��������������� ����������
 */
defkey()
{
    char bufc[LKEY+1], *buf;
    register int lc;
    struct viewport *curp;
    int curl,curc;
    register char *c,*c1;
    int lread1;
    curp = curport; 
    curc = cursorcol; 
    curl = cursorline;
    switchport(&paramport);
    poscursor(22,0);
    telluser(DIAG(" enter <new key><del>:","������� <����� �������><�����>:"),0);
    lc = 0;
    while((bufc[lc] = read2()) !='\177'  && lc++ < LKEY);
    if ( lc ==0 || lc == LKEY )
    {
        goto reterr;
    }
    bufc[lc] = 0;
    telluser(DIAG("enter <command> or <macro name>:","������� ������� ��� ��� �����"),1);
    poscursor(33,0);
    lread1= readch();
    if (!ISACMD(lread1)) {
        if(lread1 == '$') lread1 = CCMAC;
        else
            if(lread1 >= 'a' && lread1 <= 'z') lread1 += CCMAC+1 -'a';
            else {
                goto reterr;
            }
    }
    telluser("",0);
    c = buf = salloc(lc + 1);
    c1 = bufc;
    while ( *c++ = *c1++);
    lc = addkey(lread1,buf);
ret:    
    switchport(curp);
    poscursor(curc,curl);
    return(lc);
reterr:
    lc = 0; 
    error(DIAG("illegal","������")); 
    goto ret;
}

/* ��������, �� ������� ������������� ����� ��� ����� */
# define MAC_EXLEN      64
/* ����. ����� ������ ����� */
# define MAC_MAXL      512
/*
 * ��������� ��� ������ � ����� � ������ ��������
 *
 * MacCreate(char *Name) - ������ ��������� �����
 * ���� Name == NULL - ��� �� ���������
 *
 * MacExpand(cmd) - ��������� �����, ���� �� ������������,
 * � �������� ���� "cmd"
 * ���������� �� ��������� ����� ������� ����� �����
 * ��� ������ 0 - ������ ��� ���������
 *
 * MacEnd(f!=0) - ��������� ���� ����� � ������� ��� � �������
 *  f == 0 - �� �������� � �������
 * MacSave(���, �����) - ��������� ��� ��������� ����� �
 * ����� "���". �� ��������� ������������ ���������� "macro".
 * (������, �� ������ ����������)
 *
 * MacRead(���) - ��������� ����� �� �����
 *
 * ����� � readch
 * extern char *M_p, *M_e;
 * #define ADD_MACRO(c) (c != CCDEFMACRO && M_p < M_e? *M_p++ = c: MacExpand(c))
 * if ( M_p ) ADD_MACRO(lread1);
 * ---
 * � ������ ����� ����� � ������ ������ ���� �������� >n, ��� n - ��� �����
 */
static char *M_buf; /* ������ ������ */
char *M_p;   /* ��������� �������� ������ � ��� ����� */
char *M_e;
static union macro *M_mac; /* ��������� ��������� ���. ����� */
MacCreate(name)
char *name;
{
        /* ������ ��, ������ �� ������, ����� ������ �������� �� ��������� */
        if ( M_p ) {
                MacEnd(0);
                error(DIAG("Recursive macro def","����������� ���. �����"));
                return(-1);
        }
        if ( !name ) name = "0";
        M_mac = mname(name,MMAC, MSMAC);
        if ( !M_mac ) return(-1);
        M_mac->mstring = (char *)0;
        M_buf = M_p = salloc(MAC_EXLEN+1);
        M_e = M_p + MAC_EXLEN;
        Mac_info[0] = '>'; Mac_info[1] = name[0];
        infmesg(Mac_info,PARAMRMAC,A_ERROR);
        return(0);
}

/* MacExpand ����������, ����� �� ������� �������� ������
 * ����� = 0 - ������ ����� ����� �����, ������ ��� �� ����������!
 */
MacExpand(cmd)
int cmd;
{
        int l;
        if ( cmd == CCQUIT || cmd == CCDEFMACRO )
        {
                MacEnd(1);
                return(0);
        }
        l = M_p - M_buf;
        if ( l > MAC_MAXL )
        {
                MacEnd(1);
                error(DIAG("Macro too long. Truncated","����� ������� �������."));
                return(0);
        }
        M_e = M_buf;
        M_buf = salloc(l*2+1);
        strcopy(M_buf,M_e);
        zFree(M_e);
        M_e = M_buf + l*2;
        M_p = M_buf + l;
        *M_p++ = cmd;
        return(cmd);
}

MacEnd(f)
int f; /* 0 - �� ����������, 1 - ���������� */
{
        Mac_info[0] = ' '; Mac_info[1] = ' ';
        infmesg(Mac_info,PARAMRMAC,A_INFO);
        if ( !M_buf || !M_mac ) {
                error(DIAG("Internal Error MAC","����. ��. �����"));
                return(-1);
        }
        if ( f && M_buf[0] )
        {
                M_mac->mstring = append(M_buf,"");
        }
        zFree(M_buf);
        M_buf = M_p = M_e = (char *)0;
        M_mac = (union macro *)0;
        return(0);
}

/*
 * MacWrite(fd) - �������� ��� ������������ ����� � ����
 * � ������������ fd
 * ��� ������ - ���������� ���������� �����
 */
MacWrite(fd)
FILE *fd;
{
        char *mm;
        register union macro *pm;
        int lc;
        int ko=0;
        for(lc = CCMAC+1;ISMACRO(lc);lc++)
        {
                pm = mmtaba[lc-CCMAC-1];
                if ( !pm ) continue;
                mm = pm->mstring;
                if ( !mm ) continue;
                ko++;
                fprintf(fd,"macro %c\n",Mnames[lc-CCMAC-1]);
                WriteMFile(mm,fd);
                fprintf(fd,".\n");
        }
        return(ko);
}
