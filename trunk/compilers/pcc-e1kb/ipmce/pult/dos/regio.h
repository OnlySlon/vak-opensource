struct word {
	long r, l;
};

struct ioregs {
	long r [16];		/* �0-�F index registers */
	long s [8];		/* ��0-��7 special registers */
	struct word a;		/* �� accumulator */
	struct word y;		/* ��� young register */
	long pc;		/* ���� address of next command */
	long cr;		/* �� command register */
	long crp;		/* ��� */
};

struct iobwr {			/* ��� */
	struct word w [8];	/* ��� */
	char wt [8];            /* ��� */
	long a [8];		/* ��� */
};

struct iobcr {			/* ��� */
	struct word w [8];	/* ��� */
	char wt [8];            /* ��� */
	long a [8];		/* ��� */
};

struct iolcm {			/* ��� */
	struct word w [32];
	char wt [32];		/* ��� */
};

struct iommu {
	unsigned pa [64];	/* ��� */
	long ma [64];           /* ��� */
	char t [64];		/* �� */
	struct word en;		/* ��� */
	struct word us;         /* ��� */
	struct word ro;         /* ��� */
	int pm;			/* ��� */
};

struct ioiru {
	unsigned long iir;	/* ��� */
	unsigned eir;		/* ���� */
	unsigned eim;		/* ��� */
	unsigned bci;		/* ��� */
	char scx;		/* ���� */
	char scr;		/* ���� */
	char scz;		/* �0�� */
	long ucr [4];		/* �� �� */
	long ucs [4];		/* � �� */
	long tm;		/* �� */
	struct word clock;	/* �� */
};

struct bchan {
	short rd;		/* ���� */
	char ris;		/* ��� */
	char rbc;		/* ����� */
	long rs;		/* ��������� � */
	short td;		/* ���� */
	char tis;		/* ��� */
	char tbc;		/* ����� */
	long ts;		/* ��������� � */
	struct word lcm [4];	/* ��� */
	char lcmt [4];		/* ���� ��� */
};