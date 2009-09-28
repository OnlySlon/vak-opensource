
# include <stdio.h>
# include <ctype.h>

# ifdef CROSS
#    include "../h/a.out.h"
# else
#    include <a.out.h>
# endif

# define W 8            /* ����� ����� � ������ */

extern long fgeth ();

struct exec hdr;        /* ��������� */
FILE *text, *rel;
int rflag, Rflag, cflag, Cflag;
int addr;

char *lcmd2 [] = {
	"��",   "���",  "���",  "���",  "��",   "��",   "����", "����",
	"��",   "�",    "���",  "���",  "��",   "���",  "���",  "���",
	"���",  "���",  "���",  "���",  "����", "����", "����", "����",
	"��",   "��",   "�����","����", "@1c",  "@1d",  "����", "@1f",
	"����", "����", "����", "����", "����", "����", "@26",  "@27",
	"���",  "���",  "���",  "���",  "���",  "���",  "���",  "���",
	"���",  "���",  "���",  "���",  "���",  "���",  "���",  "���",
	"���",  "���",  "���",  "��",   "���",  "����", "����", "@3f",
	"���",  "����", "����", "����", "���",  "���",  "�����","�����",
	"���",  "��",   "����", "����", "���",  "����", "@4e",  "����",
	"����", "����", "����", "����", "���",  "���",  "�����","�����",
	"@58",  "@59",  "@5a",  "@5b",  "@5c",  "@5d",  "@5e",  "@5f",
	"��.",  "���.", "���.", "���.", "��.",  "��.",  "����.","����.",
	"��.",  "�.",   "���.", "���.", "��.",  "���.", "���.", "���.",
	"���.", "���.", "���.", "���.", "����.","����.","����.","@77",
	"���.", "���.", "���.", "���.", "���.", "���.", "����.","���.",

	"@80",  "@81",  "@82",  "@83",  "@84",  "@85",  "@86",  "@87",
	"@88",  "@89",  "@8a",  "@8b",  "@8c",  "@8d",  "@8e",  "@8f",
	"@90",  "@91",  "@92",  "@93",  "@94",  "@95",  "@96",  "@97",
	"@98",  "@99",  "@9a",  "@9b",  "@9c",  "@9d",  "@9e",  "@9f",
	"@a0",  "@a1",  "@a2",  "@a3",  "@a4",  "@a5",  "@a6",  "@a7",
	"@a8",  "@a9",  "@aa",  "@ab",  "@ac",  "@ad",  "@ae",  "@af",
	"@b0",  "@b1",  "@b2",  "@b3",  "@b4",  "@b5",  "@b6",  "@b7",
	"@b8",  "@b9",  "@ba",  "@bb",  "@bc",  "@bd",  "@be",  "@bf",
	"@c0",  "@c1",  "@c2",  "@c3",  "@c4",  "@c5",  "@c6",  "@c7",
	"@c8",  "@c9",  "@ca",  "@cb",  "@cc",  "@cd",  "@ce",  "@cf",
	"@d0",  "@d1",  "@d2",  "@d3",  "@d4",  "@d5",  "@d6",  "@d7",
	"@d8",  "@d9",  "@da",  "@db",  "@dc",  "@dd",  "@de",  "@df",
	"@e0",  "@e1",  "@e2",  "@e3",  "@e4",  "@e5",  "@e6",  "@e7",
	"@e8",  "@e9",  "@ea",  "@eb",  "@ec",  "@ed",  "@ee",  "@ef",
	"@f0",  "@f1",  "@f2",  "@f3",  "@f4",  "@f5",  "@f6",  "@f7",
	"@f8",  "@f9",  "@fa",  "@fb",  "@fc",  "@fd",  "@fe",  "@ff",
};

char *lcmd1 [] = {
	"atx",  "stx",  "xtra", "xts",  "aadx", "asux", "xsua", "amsx",
	"xta",  "aax",  "aex",  "arx",  "avx",  "aox",  "adx",  "amux",
	"apkx", "aux",  "acx",  "anx",  "eax",  "esx",  "asrx", "xtr",
	"uj",   "vjm",  "vgm",  "vlm",  "@1c",  "@1d",  "alx",  "@1f",
	"vzm",  "vim",  "vpzm", "vnm",  "vnzm", "vpm",  "@26",  "@27",
	"uz",   "ui",   "upz",  "un",   "unz",  "up",   "uiv",  "uzv",
	"xtga", "xtqa", "xtha", "xtta", "ztx",  "atcx", "ath",  "atgx",
	"pctm", "atc",  "utcs", "wtc",  "vtm",  "utm",  "do",   "@3f",
	"xtal", "xtsl", "utra", "uts",  "aadu", "asuu", "usua", "amu",
	"uta",  "aau",  "aeu",  "aru",  "avu",  "aou",  "@4e",  "amuu",
	"apu",  "auu",  "acu",  "anu",  "@54",  "@55",  "@56",  "@57",
	"@58",  "@59",  "@5a",  "@5b",  "@5c",  "@5d",  "@5e",  "@5f",
	"atk",  "stk",  "ktra", "kts",  "aadk", "asuk", "ksua", "amk",
	"kta",  "aak",  "aek",  "ark",  "avk",  "aok",  "adk",  "amuk",
	"apk",  "auk",  "ack",  "ank",  "eak",  "esk",  "ask",  "@77",
	"ktga", "ktsa", "ktha", "ktta", "ztk",  "atck", "alk",  "atgk",

	"@80",  "@81",  "@82",  "@83",  "@84",  "@85",  "@86",  "@87",
	"@88",  "@89",  "@8a",  "@8b",  "@8c",  "@8d",  "@8e",  "@8f",
	"@90",  "@91",  "@92",  "@93",  "@94",  "@95",  "@96",  "@97",
	"@98",  "@99",  "@9a",  "@9b",  "@9c",  "@9d",  "@9e",  "@9f",
	"@a0",  "@a1",  "@a2",  "@a3",  "@a4",  "@a5",  "@a6",  "@a7",
	"@a8",  "@a9",  "@aa",  "@ab",  "@ac",  "@ad",  "@ae",  "@af",
	"@b0",  "@b1",  "@b2",  "@b3",  "@b4",  "@b5",  "@b6",  "@b7",
	"@b8",  "@b9",  "@ba",  "@bb",  "@bc",  "@bd",  "@be",  "@bf",
	"@c0",  "@c1",  "@c2",  "@c3",  "@c4",  "@c5",  "@c6",  "@c7",
	"@c8",  "@c9",  "@ca",  "@cb",  "@cc",  "@cd",  "@ce",  "@cf",
	"@d0",  "@d1",  "@d2",  "@d3",  "@d4",  "@d5",  "@d6",  "@d7",
	"@d8",  "@d9",  "@da",  "@db",  "@dc",  "@dd",  "@de",  "@df",
	"@e0",  "@e1",  "@e2",  "@e3",  "@e4",  "@e5",  "@e6",  "@e7",
	"@e8",  "@e9",  "@ea",  "@eb",  "@ec",  "@ed",  "@ee",  "@ef",
	"@f0",  "@f1",  "@f2",  "@f3",  "@f4",  "@f5",  "@f6",  "@f7",
	"@f8",  "@f9",  "@fa",  "@fb",  "@fc",  "@fd",  "@fe",  "@ff",
};

char *scmd2 [] = {
	"��",   "���",  "���",  "���",  "$04",  "$05",  "���",  "����",
	"$08",  "$09",  "$0a",  "$0b",  "$0c",  "$0d",  "$0e",  "$0f",
	"$10",  "���",  "$12",  "$13",  "���",  "$15",  "���",  "$17",
	"���",  "��",   "����", "���",  "���",  "���",  "���",  "���",
	"��",   "���",  "��",   "���",  "���",  "���",  "�����","���",
	"��",   "���",  "��",   "$2b",  "���",  "$2d",  "$2e",  "$2f",
	"$30",  "$31",  "$32",  "$33",  "����", "����", "����", "$37",
	"����", "$39",  "$3a",  "$3b",  "���",  "$3d",  "����", "���",
	"$40",  "$41",  "$42",  "$43",  "$44",  "$45",  "$46",  "$47",
	"$48",  "$49",  "$4a",  "$4b",  "$4c",  "$4d",  "$4e",  "$4f",
	"$50",  "����", "$52",  "$53",  "����", "$55",  "����", "$57",
	"����", "���",  "�����","$5b",  "����", "����", "����", "����",
	"$60",  "$61",  "���",  "����", "$64",  "$65",  "$66",  "$67",
	"$68",  "$69",  "���",  "$6b",  "$6c",  "$6d",  "$6e",  "$6f",
	"$70",  "$71",  "$72",  "$73",  "�����","�����","�����","$77",
	"�����","$79",  "$7a",  "$7b",  "����", "$7d",  "�����","����",

	"$80",  "$81",  "$82",  "$83",  "$84",  "$85",  "$86",  "$87",
	"$88",  "$89",  "$8a",  "$8b",  "$8c",  "$8d",  "$8e",  "$8f",
	"$90",  "$91",  "$92",  "$93",  "$94",  "$95",  "$96",  "$97",
	"$98",  "$99",  "$9a",  "$9b",  "$9c",  "$9d",  "$9e",  "$9f",
	"$a0",  "$a1",  "$a2",  "$a3",  "$a4",  "$a5",  "$a6",  "$a7",
	"$a8",  "$a9",  "$aa",  "$ab",  "$ac",  "$ad",  "$ae",  "$af",
	"$b0",  "$b1",  "$b2",  "$b3",  "$b4",  "$b5",  "$b6",  "$b7",
	"$b8",  "$b9",  "$ba",  "$bb",  "$bc",  "$bd",  "$be",  "$bf",
	"$c0",  "$c1",  "$c2",  "$c3",  "$c4",  "$c5",  "$c6",  "$c7",
	"$c8",  "$c9",  "$ca",  "$cb",  "$cc",  "$cd",  "$ce",  "$cf",
	"$d0",  "$d1",  "$d2",  "$d3",  "$d4",  "$d5",  "$d6",  "$d7",
	"$d8",  "$d9",  "$da",  "$db",  "$dc",  "$dd",  "$de",  "$df",
	"$e0",  "$e1",  "$e2",  "$e3",  "$e4",  "$e5",  "$e6",  "$e7",
	"$e8",  "$e9",  "$ea",  "$eb",  "$ec",  "$ed",  "$ee",  "$ef",
	"$f0",  "$f1",  "$f2",  "$f3",  "$f4",  "$f5",  "$f6",  "$f7",
	"$f8",  "$f9",  "$fa",  "$fb",  "$fc",  "$fd",  "$fe",  "$ff",
};

char *scmd1 [] = {
	"ex",   "pop",  "rmod", "ij",   "$04",  "$05",  "wmod", "halt",
	"$08",  "$09",  "$0a",  "$0b",  "$0c",  "$0d",  "$0e",  "$0f",
	"$10",  "yma",  "$12",  "$13",  "ecn",  "$15",  "asn",  "$17",
	"rta",  "yta",  "een",  "set",  "ean",  "esn",  "aln",  "ntr",
	"ati",  "sti",  "ita",  "iita", "mtj",  "jam",  "msj",  "jsm",
	"ato",  "sto",  "ota",  "$2b",  "mto",  "$2d",  "$2e",  "$2f",
	"$30",  "$31",  "$32",  "$33",  "ent",  "int",  "asy",  "$37",
	"atia", "$39",  "$3a",  "$3b",  "aca",  "$3d",  "aly",  "tst",
	"$40",  "$41",  "$42",  "$43",  "$44",  "$45",  "$46",  "$47",
	"$48",  "$49",  "$4a",  "$4b",  "$4c",  "$4d",  "$4e",  "$4f",
	"$50",  "yms",  "$52",  "$53",  "ecns", "$55",  "asns", "$57",
	"rts",  "yts",  "eens", "$5b",  "eans", "esns", "alns", "ntrs",
	"$60",  "$61",  "its",  "iits", "$64",  "$65",  "$66",  "$67",
	"$68",  "$69",  "ots",  "$6b",  "$6c",  "$6d",  "$6e",  "$6f",
	"$70",  "$71",  "$72",  "$73",  "ents", "ints", "asys", "$77",
	"atis", "$79",  "$7a",  "$7b",  "acs",  "$7d",  "alys", "tsts",

	"$80",  "$81",  "$82",  "$83",  "$84",  "$85",  "$86",  "$87",
	"$88",  "$89",  "$8a",  "$8b",  "$8c",  "$8d",  "$8e",  "$8f",
	"$90",  "$91",  "$92",  "$93",  "$94",  "$95",  "$96",  "$97",
	"$98",  "$99",  "$9a",  "$9b",  "$9c",  "$9d",  "$9e",  "$9f",
	"$a0",  "$a1",  "$a2",  "$a3",  "$a4",  "$a5",  "$a6",  "$a7",
	"$a8",  "$a9",  "$aa",  "$ab",  "$ac",  "$ad",  "$ae",  "$af",
	"$b0",  "$b1",  "$b2",  "$b3",  "$b4",  "$b5",  "$b6",  "$b7",
	"$b8",  "$b9",  "$ba",  "$bb",  "$bc",  "$bd",  "$be",  "$bf",
	"$c0",  "$c1",  "$c2",  "$c3",  "$c4",  "$c5",  "$c6",  "$c7",
	"$c8",  "$c9",  "$ca",  "$cb",  "$cc",  "$cd",  "$ce",  "$cf",
	"$d0",  "$d1",  "$d2",  "$d3",  "$d4",  "$d5",  "$d6",  "$d7",
	"$d8",  "$d9",  "$da",  "$db",  "$dc",  "$dd",  "$de",  "$df",
	"$e0",  "$e1",  "$e2",  "$e3",  "$e4",  "$e5",  "$e6",  "$e7",
	"$e8",  "$e9",  "$ea",  "$eb",  "$ec",  "$ed",  "$ee",  "$ef",
	"$f0",  "$f1",  "$f2",  "$f3",  "$f4",  "$f5",  "$f6",  "$f7",
	"$f8",  "$f9",  "$fa",  "$fb",  "$fc",  "$fd",  "$fe",  "$ff",
};

char **lcmd = lcmd1, **scmd = scmd1;

# define MSG(l,r) (msg ? (r) : (l))

char msg;

initmsg ()
{
	register char *p;
	extern char *getenv ();

	msg = (p = getenv ("MSG")) && *p == 'r';
}

main (argc, argv)
register char **argv;
{
	int yesarg;     /* ���� �� ��������� - ����� ������ */

	initmsg ();
	yesarg = 0;
	while(--argc) {
		++argv;
		if (**argv == '-') {
			register char *cp;

			for (cp = *argv+1; *cp; cp++) switch (*cp) {
			case 'R':       /* print relocation in hexadecimal */
				Rflag++;
			case 'r':       /* print relocation info */
				rflag++;
				break;
			case 'C':       /* print commands only in hex */
				Cflag++;
			case 'c':       /* print commands in hexadecimal */
				cflag++;
				break;
			case 'b':       /* use BEMSH mnemonics */
				lcmd = lcmd2;
				scmd = scmd2;
				break;
			default:
				fprintf (stderr, "Usage: dis [-bcrR] file...\n");
				return (1);
			}
		} else {
			dis (*argv);
			yesarg = 1;
		}
	}
	if (! yesarg) dis ("a.out");
	return (0);
}

dis (fname)
register char *fname;
{
	if ((text = fopen (fname, "r")) == NULL) {
		fprintf (stderr, MSG ("dis: %s not found\n",
				"dis: %s �� ������\n"),
			fname);
		return;
	}
	if (! fgethdr (text, &hdr) || N_BADMAG (hdr)) {
		fprintf (stderr, MSG ("dis: %s not an object file\n",
				"dis: %s �� ��������� ����\n"),
			fname);
		return;
	}
	if (rflag) {
		if (hdr.a_flag & RELFLG) {
			fprintf (stderr, MSG ("dis: %s is not relocatable\n",
					"dis: %s ��������������\n"),
				fname);
			return;
		}
		if ((rel = fopen (fname, "r")) == NULL) {
			fprintf (stderr, MSG ("dis: %s not found\n",
					"dis: %s �� ������\n"),
				fname);
			return;
		}
		fseek (rel, N_SYMOFF (hdr), 0);
	}
	disfile ();
}

disfile ()
{
	addr = HDRSZ/W;
	if (! (hdr.a_flag & TCDFLG)) {
		prconst ((int) hdr.a_const/W);
		putchar ('\n');
	}
	prtext ((int) hdr.a_text/W);
	putchar ('\n');
	if (hdr.a_flag & TCDFLG) {
		prconst ((int) hdr.a_const/W);
		putchar ('\n');
	}
	prdata ((int) hdr.a_data/W);
}

prconst (n)
register n;
{
	register long c, r;

	while (n--) {
		c = fgeth (text);
		printf ("x%x:\t%08lx%08lx", addr++, fgeth (text), c);
		if (rflag) {
			putchar ('\t');
			r = fgeth (rel);
			prrel (fgeth (rel));
			putchar (' ');
			prrel (r);
		}
		putchar ('\n');
	}
}

prtext (n)
register n;
{
	register long c, r;

	while (n--) {
		printf ("x%x:", addr++);
		c = fgeth (text);
		prcmd (fgeth (text));
		if (rflag) {
			putchar ('\t');
			r = fgeth (rel);
			prrel (fgeth (rel));
		}
		putchar ('\n');
		prcmd (c);
		if (rflag) {
			putchar ('\t');
			prrel (r);
		}
		putchar ('\n');
	}
}

prdata (n)
register n;
{
	register long c, r;

	while (n--) {
		c = fgeth (text);
		printf ("x%x:\t%08lx%08lx", addr++, fgeth (text), c);
		if (rflag) {
			putchar ('\t');
			r = fgeth (rel);
			prrel (fgeth (rel));
			putchar (' ');
			prrel (r);
		}
		putchar ('\n');
	}
}

char *addrtoa (a)
register long a;
{
	static char buf [20];
	register char *p;
	int sign;

	if (a & 0x80000L)
		a -= 0x100000L;
	if (a>=0 && a<16 || a<0 && a>-16) {
		sprintf (buf, "%ld", a);
		return (buf);
	}
	p = buf + sizeof (buf);
	*--p = 0;
	sign = 0;
	if (a < 0) {
		sign = 1;
		a = -a;
	}
	if (a >= 0x10)
		*--p = 'h';
	do
		*--p = "0123456789abcdef" [a & 0xf];
	while (a >>= 4);
	if (*p > '9')
		*--p = '0';
	if (sign)
		*--p = '-';
	return (p);
}

prmnem (c)
register long c;
{
	register r;
	register long a;

	if (r = (c >> 28) & 017) printf ("\t%2d ", r); else printf ("\t   ");
	if ((c & 0xff00000L) == 0x3f00000L) {
		printf (scmd [c>>12 & 0377]);
		a = c & 0xfff;
	} else {
		printf (lcmd [c>>20 & 0377]);
		a = c & 0xfffff;
	}
	if (a) printf (" %-7s\t", addrtoa (a)); else printf ("       \t");
}

prcmd (c)
register long c;
{
	register r;
	register long a;

	if (! Cflag)
		prmnem (c);
	if (cflag)
		printf ("\t%08x\t", c);
}

prrel (r)
register long r;
{
	if (Rflag) {
		printf ("%d %d", (int) (r & REXT) >> 3, (int) (r & RSHORT));
		if (RGETIX (r))
			printf (" %d", (int) RGETIX (r));
		return;
	}
	switch ((int) r & REXT) {
	default:        putchar ('?');  break;
	case RCONST:    putchar ('c');  break;
	case RTEXT:     putchar ('t');  break;
	case RDATA:     putchar ('d');  break;
	case RBSS:      putchar ('b');  break;
	case RABSS:     putchar ('y');  break;
	case RABS:      putchar ('a');  break;
	case REXT:      printf ("%d", (int) RGETIX (r));
	}
	switch ((int) r & RSHORT) {
	case RLONG:     putchar ('l');  break;
	case RSHORT:    putchar ('s');  break;
	case RSHIFT:    putchar ('h');  break;
	case RTRUNC:    putchar ('t');  break;
	case 0:         putchar ('a');  break;
	default:        putchar ('?');  break;
	}
}
