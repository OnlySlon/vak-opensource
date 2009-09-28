# include "regio.h"

# define A 22
# define C 8
# define X 10

# define Y (9+X)
# define Z (5+X)
# define B (40+A)
# define D (40+C)

# define BIT(i)		(1L << (i))

struct bcstate {
	int row, col;
	char *name;
};

static struct bcstate rstate [] = {
	X,	B,	"���",
	X+1,	B,	"���",
	X+2,	B,	"���",
	X+3,	B,	"�����",
	X+4,	B,	"����(�)",
	X+5,	B,	"��",
	X+6,	B,	"�������(�)",
	X+7,	B,	"����",
	Y,	B,	"���",
	Y+1,	B,	"���",
	Y+2,	B,	"���",
	Y+3,	B,	"��12",
	Z,	D,	"����",
	Z+1,	D,	"����",
	Z+2,	D,	"����",
	Z+3,	D,	"����",
	Z+4,	D,	"����",
	Z+5,	D,	"���",
	Z+6,	D,	"����",
	Z+7,	D,	"����",
};

static struct bcstate tstate [] = {
	X,	A,	0,
	X+1,	A,	"���",
	X+2,	A,	"���",
	X+3,	A,	"�����",
	X+4,	A,	"�������(�)",
	X+5,	A,	"��",
	X+6,	A,	"����(�)",
	X+7,	A,	"����",
	Y,	A,	0,
	Y+1,	A,	"����",
	Y+2,	A,	"��",
	Y+3,	A,	"���",
	Z,	C,	"����",
	Z+1,	C,	"����",
	Z+2,	C,	"����",
	Z+3,	C,	"����",
	Z+4,	C,	"���",
	Z+5,	C,	"���",
	Z+6,	C,	0,
	Z+7,	C,	0,
};

extern halting;				/* ��������� ����� */

extern long ptrecvl ();

notyet ()
{
	win0 ();
	Jmove (22, 30);
	Jrbold (0x4e);
	Jprintf ("��� �� �����������");
	Jnorm (0x1b);
}

bc0 () { bc (0); }
bc1 () { bc (1); }
bc2 () { bc (2); }
bc3 () { bc (3); }
bc4 () { bc (4); }
bc5 () { bc (5); }
bc6 () { bc (6); }
bc7 () { bc (7); }

bc (n)
{
	register i;
	struct bchan b;

	loadbchan (n, &b);
	Jmprintf (2, 30, "�������� ����� %d", n);
	Jmprintf (4, 10, "�������� %d", n);
	Jmprintf (4, 50, "�������� %d", n);

	Jmprintf (6, 5, "���  ");
	prbclcm (&b, 0);
	Jmprintf (7, 5, "���  ");
	prbclcm (&b, 1);
	Jmprintf (6, 45, "���  ");
	prbclcm (&b, 2);
	Jmprintf (7, 45, "���  ");
	prbclcm (&b, 3);

	Jmprintf (X, C-1, "%02x  ����", b.td);
	Jmprintf (X, D-1, "%02x  ����", b.rd);
	Jmprintf (X+1, C, "%x  ���", b.tis);
	Jmprintf (X+1, D, "%x  ���", b.ris);
	Jmprintf (X+2, C, "%x  ����", b.tbc);
	Jmprintf (X+2, D, "%x  ����", b.rbc);

	for (i=0; i<20; ++i) {
		prbcstate (&tstate[i], b.ts & BIT (i) ? '1' : '0');
		prbcstate (&rstate[i], b.rs & BIT (i) ? '1' : '0');
	}
}

prbclcm (b, n)
register struct bchan *b;
register n;
{
	prword (&b->lcm[n]);
	Jprintf ("  %02x", b->lcmt [n] & 0xff);
}

static prbcstate (s, c)
register struct bcstate *s;
{
	if (s->name)
		Jmprintf (s->row, s->col, "%c  %s", c, s->name);
}

static loadbchan (n, r)
register n;
register struct bchan *r;
{
	register long h;
	register i;

	/* enable access to cpu registers */
	stop ();
	ptenable ();

	r->rd = ptrecvb (0100|n, 0334) & 0xff;
	r->td = ptrecvb (0100|n, 0324) & 0xff;

	r->ris = ptrecvb (0100|n, 0333) & 0xf;
	r->tis = ptrecvb (0100|n, 0323) & 0xf;

	r->rbc = ptrecvb (0100|n, 0335) >> 4 & 0xf;
	r->tbc = ptrecvb (0100|n, 0325) >> 4 & 0xf;

	h = ptrecvb (0100|n, 0332) & 0xff;
	h |= (long) (ptrecvb (0100|n, 0335) & 0xf) << 8;
	h |= (long) (ptrecvb (0100|n, 0336) & 0xff) << 12;
	r->rs = h;

	h = ptrecvb (0100|n, 0322) & 0xff;
	h |= (long) (ptrecvb (0100|n, 0325) & 0xf) << 8;
	h |= (long) (ptrecvb (0100|n, 0326) & 0xff) << 12;
	r->ts = h;

	for (i=0; i<4; ++i)
		load1lcm (&r->lcm[i], &r->lcmt[i], 32+n*4+i);

	/* disable access to cpu registers */
	if (! halting)
		run ();
}
