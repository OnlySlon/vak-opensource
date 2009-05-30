/*
 *      ���� low.c - �������-��������� ����� �������,
 *      ��������� � ��������.
 *
 *      �������:
 *
 *      subroutine begin (nx, ny)
 *      integer nx
 *      integer ny
 *
 *              - ��������� ������������ ������. ������������ ��������
 *              ����������� ���������, ������� �������������� ������������,
 *              ������ � nx � ny. ���� ��������������� � ����� 0, 0.
 *
 *      subroutine end
 *
 *              - ���������� ������������ ������.
 *
 *      subroutine plot (nx, ny, k)
 *      integer nx
 *      integer ny
 *      integer k
 *
 *              - ����������� ���� � ����� nx, ny. ���� k==2, �����������
 *              ���������� � �������� ����� (��������� �����), ����� - �
 *              �������� (��������� �������).
 *
 *      subroutine setpen (n)
 *      integer n
 *
 *              - ��������� ����� ���� � ������� n. �� ��������� - 1.
 *
 *      subroutine setmtf (name, len)
 *      character name (len)
 *      integer len
 *
 *              - ������� ����� ��������� ��� ������ �������. ����� len �����
 *              name �� ������ ��������� 14 ��������.
 *
 *      subroutine setscr
 *
 *              - ������� ������ ������� �� �������.
 *
 *      subroutine commnt (s, len)
 *      character s (len)
 *      integer len
 *
 *              - ������ ����������� s ������ len � ��������.
 *
 *      subroutin� paint (nx, ny, n)
 *      integer nx
 *      integer ny
 *      integer n
 *
 *              - ������� ������ �� ����� nx, ny �� ������� ������ n.
 */

/*
 *      � ��������� ������ �������������� ��� ����������
 *      � ������ ����� �� � ���������:
 *
 *      1.      ��� ������ �������-������� �� �� � ����� ����� ��������
 *              �������. ������� ���������� - ��� ��. ���������
 *              ���������� �� ������. ���� integer � real � ��������
 *              ������������� long � float � ��.
 *              ������������ �� ���������.
 *
 *      2.      ��� ������ �������-������� �� �� �� ����� �������
 *              �������� ������ fortran. ������� ���������� - ��� ��.
 *              ��������� ���������� �� ������. ���� integer � real �
 *              �������� ������������� long � float � ��.
 *              ���������� ������ -DMSF.
 */

# ifdef MSF
#       define  BEGIN   fortran Begin
#       define  END     fortran End
#       define  SETPEN  fortran Setpen
#       define  PLOT    fortran Plot
#       define  SETSCR  fortran Setscr
#       define  SETMTF  fortran Setmtf
#       define  PAINT   fortran Painta
#       define  COMMNT  fortran Commnt
#       define  GRINIT  Grinit
# else
#       define  BEGIN   begin_
#       define  END     end_
#       define  SETPEN  setpen_
#       define  PLOT    plot_
#       define  SETSCR  setscr_
#       define  SETMTF  setmtf_
#       define  PAINT   painta_
#       define  COMMNT  commnt_
#       define  GRINIT  grinit_
# endif

# ifdef MSF
extern fortran GRINIT ();
# endif

# define INTEGER long

static graflag;                         /* if graph regime is on */
static scrflag = 1;                     /* use screen (1) or metafile (0) */

static grinit () { GRINIT (); }         /* dummy call - load block data */

BEGIN (x, y)
INTEGER *x, *y;
{
	/* check if grafor is already opened */
	if (graflag)
		return;

	/* try to initialize graph library */
	if (! GOpen (scrflag, (int) *x, (int) *y))
		return;

	/* grafor is opened */
	graflag = 1;
}

END ()
{
	if (! graflag)
		return;
	GClose ();
	graflag = 0;
}

PLOT (x, y, k)
INTEGER *x, *y, *k;
{
	if (! graflag)
		return;
	if (*k == 2)
		GPlot ((int) *x, (int) *y);
	else
		GMove ((int) *x, (int) *y);
}

SETPEN (n)
INTEGER *n;
{
	GColor ((int) *n);
}

SETMTF (name, len)
char *name;
INTEGER *len;
{
	char buf [40];

	if (graflag)
		return;
	strcopy (buf, sizeof (buf), name, (int) *len);
	if (GFile (buf))
		scrflag = 0;
	else
		scrflag = 1;
}

SETSCR ()
{
	if (graflag)
		return;
	scrflag = 1;
}

COMMNT (s, len)
char *s;
INTEGER *len;
{
	char buf [100];

	if (! graflag)
		return;
	strcopy (buf, sizeof (buf), s, (int) *len);
	GComment (buf);
}

PAINT (n, x, y)
INTEGER *n, *x, *y;
{
	if (! graflag)
		return;
	GPaint ((int) *n, (int) *x, (int) *y);
}

static strcopy (dest, dsz, src, ssz)
register char *dest, *src;
{
	register i;

	i = ssz < dsz ? ssz : dsz-1;
	while (--i >= 0)
		*dest++ = *src++;
	*dest = 0;
}
