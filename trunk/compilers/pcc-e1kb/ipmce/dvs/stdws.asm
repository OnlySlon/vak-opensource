 MO���� 'CEPB�C_�BC'
***************************************************
*                                                 *
*     CEPB�CH�� �AKET �PO�E��P ��C�ET�EPA         *
*           B�PT�A��H�X C�CTEM(�BC)               *
*               �TM � BT AH CCCP                  *
*                    1989 �.                      *
*                                                 *
*                                                 *
*B��OP �PO�E��P� O�PE�E�EH CO�EP��M�M �� 'B��_PA�'*
*                                                 *
*��� ���O� �PO�E��P� HEO�XO��MO �A�AH�E O�'��A -  *
*TE��H�X �APAMETPOB: 'HOM_KAH','HOM_�CT','�M�_P�' *
*                                                 *
*B��_PA�=0 - PA�METKA ��CKA � CO��AH�E HA HEM MET-*
*            K� TOMA.                             *
*  '����ND�' TEK���E KOOP��HAT� PA�METK�          *
*�APAMETP� : 'PA�MEP_P�','��C�O_P�','�M�_P�'.     *
*                                                 *
*B��_PA�=1 - CTAPT ��C�E�EPA B�PT�A��H�X C�CTEM   *
*�APAMETP� : '���_�A�','HOM_��O','A�P_O��', 'KO�_ *
*             �A�'                                *
*                                                 *
*B��_PA�=2 - �EPE��C� C O�EPAT�BHO� �AM�T� HA ��CK*
*�APAMETP� : '���_�A�','HOM_��O','A�P_O��', '��A_ *
*            �TE','KO�_�A�'.                      *
*                                                 *
*B��_PA�=3 - ��CKOB�� TECT                        *
*�APAMETP� : �A�O�H�T� MACC�B 'O�EPE��',CM.TA��.  *
*                                                 *
*B��_PA�=4 - �EPEPA�METKA �OPO�K�,�P� �TOM �E�AET-*
*            C� �O��TKA COXPAHEH�� �A��CE� HA �TO�*
*            �OPO�KE.                             *
*�APAMETP� : 'HOM_��O','��A_�TE'                  *
*                                                 *
*B��_PA�=5 - CO��AH�E PA��E�A(P�) TOMA            *
*�APAMETP� : 'PA�MEP_P�','�M�_P�'.                *
*                                                 *
*      KOT : 1 HET MECTA ��� O��CATE�� P�         *
*            2 HET �POCTPAHCTBA ���  P�           *
*            3 TAKOE �M� P� ��E ECT�              *
*                                                 *
*B��_PA�=6 - �CK���EH�E �� ��PEKTOP�� P�          *
*�APAMETP� : '�M�_P�'.                            *
*                                                 *
*      KOT : 1 HET TAKO�O P�                      *
*                                                 *
*B��_PA�=7 - �EPE��C� C MA�H�THO� �EHT� HA ��CK.  *
*�APAMETP� : 'HOM_�A�_M�','HOM_KAH_M�','HOM_�CT_M�*
*            'HOM_��O','��A_�TE'.                 *
*                                                 *
*B��_PA�=8 - �A�P��KA �PO�PAMM� �� M� ��C�AKA     *
*�APAMETP� : 'HOM_��O' HOMEP �OH� ��C�AKA         *
*                                                 *
*                                                 *
***************************************************
 
 
KH CEK��� 0,�20,��KT,CBO�
KH:��OK;�OKA��H�E ��E�K� KAHA�A
!�APAMETP� �PA�BEPA
L_C�:�KB 3;KO� C��� C�OB
L_��O:�KB 128+L_C�;���HA ��OKA
L_��T:�KB /(9*L_��O+8+7)//8;���HA ��OKA �E� TE�A
L_K�A:�KB 32;K�ACTEP O�MEHA
L_K�P:�KB L_K�A*3+L_K�A/L_�A�MIN+2;MAX ���HA KAH �PO
L_�A�MIN:�KB 10;M�H�MA��HOE ��C�O �A� HA �OPO�KE
L_�A�MAX:�KB 20;MAKC�MA��HOE ��C�O �A� HA �OPO�KE
!
�CTP:�AM
KKOM:�AM
N�A�:�AM
K�A�:�AM
���K:�AM L_��O*L_K�A+L_��O/8+1
����N:�AM L_K�A+L_K�A/L_�A�MIN+2
KAH_�PO:�AM L_K�P*2
L_KH:�KB #-KH
 K��OK KH
 
 
CEPB�C CEK��� 0,�20,�KOM
��CK� ��OK BK�=KH
 �AM
BXO� ��A CTEK(S)
 �� HA�
: �� ;BHE_�PE
: CTO� 3;P�=3 �KCTPAKO�
: CTO� 4;P�=1
: CTO� 5;P�=1
: CTO� 6;P�=3 BH�_�PE
 BP� 1FH;P�P
: CTO� 7;P�=3 �A�P_KOM
 �� BXO�
B��_PA� KOH� 0
PA�MEP_P� KOH� 808*19*10;153 520 /200/
��C�O_P� KOH� 256
�M�_P� TEKCT T''0'C�C_�AK_���'
 �AM 8
HOM_�A�_M� KOH� 3;�C�O����TC� �P� �TEH�� C M�
HOM_KAH_M� KOH� 3
HOM_�CT_M� KOH� 2
 
KO�_�A� KOH� 100H
A�P_O�� KOH� 1 0000H
HOM_��O KOH� 100H
��A_�TE KOH� 1
���_�A� �AM;KO� �A� C�/�� �A O��H O�MEH <32
HOM_�CT KOH� 1
HOM_KAH KOH� 0
CET_HOM KOH� 038000000 00000000H;A�PECA A�OHEHTOB
 KOH� 058000000 00000008H
 KOH� 0D8000000 00000010H
 KOH� 080000000 00000018H
O�EPE�� KOH� 0 2 3 07 0 1 0 100 01 E00H
 KOH� 0 2 3 0F 0 1 0 2BA 0C E00H
 KOH� 0 0 0 04 0 1 1 100 01 000H
 KOH� 0 1 0 0F 1 1 1 100 01 000H
***************************************************
*     [64:61] -- HOM_KAH
*     [60:57] -- HOM_�CT
*     [56:53] -- HOM_�AK
*     [51:45] -- ���_�A�
*     [44:41] -- 0-�T,1-��
*     [40:37] -- ��A_�TE
*     [36:33] -- 1-RANDOM
*     [32:21] -- ����
*     [20:13] -- ��
*     [12:01] -- ���HA
***************************************************
�C1 �KB 9
�C2 �KB 10
�C3 �KB 11
�C7 �KB 15
R1 �KB 1
R2 �KB 2
R3 �KB 3
R4 �KB 4
R5 �KB 5
R6 �KB 6
R7 �KB 7
R8 �KB 8
R9 �KB 9
RA �KB 10
RB �KB 11
RC �KB 12
R �KB 13
W �KB 14
S �KB 15
���_CTA �KB 3000H
���EP �KB 4000H
TA�_�E� �KB METKA_TOMA+6
MAC_�TE �KB TA�_�E�+256;
MAC_TEC �KB MAC_�TE+L_��O*L_K�A
CTEK �KB MAC_TEC+2*L_��T*L_�A�MAX
C�C� �KB CTEK+100
K�OB �KB C�C�+4
�O�_��P �KB K�OB+4;�C3,�C7,�P1-�P13,�P14,�P15
��N �KB �O�_��P
�CK �AM
����ND� �AM 1; TEK���� ���� �P� PA�METKE
CCK �AM
��C �AM 3
ACK �AM
A���C �AM
PA� �AM
MACKA KOH� [64:61]0CH
MAC_KAH KOH� [64:61]9H
HA�_��OK �AM
KOH_��OK �AM
HOM_�O� �AM
HOM_�A� �AM
KO�_�OP �AM
��C_�OP_�AM �AM
X �AM
����� �AM
 KOH� [49]00 80H;HET �E�EKTOB HA �OPO�KE
����� �AM
  
! �APAMETP� �CTPO�CTBA
   
�_�O� KOH� 19;��C�O �O�OBOK
�_��� KOH� 808;��C�O �H�OPM ����H�POB
�_���� KOH� 814;�O�HOE ��C�O ��� HA �AKETE
O_�OP KOH� 13440;O�'EM �OPO�K� B �A�TAX
!   
�_�A� �AM
�_�A�O �AM;O�PATH�E BE����H�
�_�O�O �AM
�_���O �AM
�_�O�� �AM
�_�A�� �AM
   
PA�M_KO�
 KOH� 05555 5555 5555 5555H
 KOH� 0D8AA AAAA AAAA AAAAH
 KOH� 0AAD8 5555 5555 5555H
 KOH� 05555 D8AA AAAA AAAAH
 KOH� 0AAAA AAD8 5555 5555H
 KOH� 05555 5555 D8AA AAAAH
 KOH� 0AAAA AAAA AAD8 5555H
 KOH� 05555 5555 5555 D8AAH
 KOH� 0AAAA AAAA AAAA AAD8H
X0 KOH� 8300 0000 0FFF FFFEH;��� XAP=0
 KOH� [25]00 08 04 0000H!HET_O��
 KOH� [25]00 FF FF 1F90H
 KOH� [25]00 4A 04 0010H!HA�O_�OB
 KOH� [25]00 FF FF 1F90H
 KOH� [25]00 4A 04 0050H!KOPT
 KOH� [25]00 FF FF 13F0H
X1 KOH� 8400 0000 0FFF FFFEH;��� XAP=1
 KOH� [33]000C 0000H!HET_O��;KB
 KOH� [33]00FF 1F90H
 KOH� [33]004E 0010H!HA�O_�OB;MKC
 KOH� [33]00FF 1F90H
 KOH� [33]0008 0000H!HET_O��;KK OKK=1
 KOH� [33]00FF 1F90H
K�T� KOH� 07 64 0000 000000H!�����;�TEH�E C ��C�AKA
 KOH� 31 54 0000 000000H!��N
 KOH� 08 04 0000 000000H!#-1
 KOH� 06 04 0004 000000H!C�C�
 KOH� 31 54 0000 000000H!��N+1
 KOH� 08 04 0000 000000H!#-1
 KOH� 06 80 0100 000000H
K�P� KOH� 1F 14 0000 000000H!MACKA
 KOH� 07 64 0000 000000H!�����
 KOH� 39 44 0000 000000H!����ND�;�O�CK CA
 KOH� 08 04 0000 000000H!#-1
 KOH� 19 34 0001 000000H!�����;CA
 KOH� 15 04 0001 000000H!����ND�;R0
K�P�$ �AM 2*L_�A�MAX+1
K��� KOH� 1F 14 0000 000000H!MACKA;�A� �P�� �E�
 KOH� 07 64 0000 000000H!�����
 KOH� 39 44 0000 000000H!����ND�;�O�CK CA
 KOH� 08 04 0000 000000H!#-1
 KOH� 19 34 0001 000000H!�����;CA
 KOH� 15 00 0001 000000H!����ND�;R0
K�CT
 KOH� 00 A4 04 0003 000000H!���_CTA;CH�T�E CTAT�CT�K�
 KOH� 00 13 04 0000 000001H
K��C KOH� 00 04 00 0003 000000H!��C
K�KP KOH� 00 31 54 0000 000000H!��C+1
 KOH� 00 08 04 0000 000000H!K�KP
 KOH� 00 08 00 0000 000000H
K�KPT �AM
 KOH� 00 08 04 0000 000000H!K�KPT
 KOH� 00 08 00 0000 000000H
 �A�A KH:RB
HA� B�T
 CTO�
 ��A -12(W)
 C�
: �� 13(W);O�H��EH�E PE��CTPOB
 ��K� #(W)
 ��A METKA_TOMA(R)
: �P�� 0FFFFH
 ��H+ 1(R)
 �B �CT(R)
 �� B��_PA�
 �� #+1
: ��A (W)
 �� PA�METKA;PA�=0
: ��A (R9);PA�=1
 �� CTAPT_�BC
: ��A (R9);PA�=2 �EPE O��->M�
 �� �EPE_O��_M�
: ��A -3(R1);PA�=3
 �� TECT_M�
: ��A PEMOHT(RA);PA�=4
 �� �TEH�E_METK�
: ��A CO�_P�(RA);PA�=5
 �� �TEH�E_METK�
: ��A �CK_P�(RA);PA�=6
 �� �TEH�E_METK�
: C� HOM_KAH;PA�=7 �EPE M�->M�
 �� �TEH�E_M�
: C� HOM_��O;PA�=8 �EPE ��C�AK->O��
 C�� 2;*4
 �� R9
 ��A 4 0000H(R1);HA� A�PEC 1-CE�MEHTA
��C C� =MAC_�TE
 C��M (R9)
 ��A K�T�(R3)
 �B O�M_��OKOM(R)
 �HP O���KA_O�MEHA
 �� (S);A�PEC O��
 ��A (W)
 ��A -255(R)
: �� (S);KOHT C�M
 C�T+ 1(W)
 C�K (S)
 ��K� #-1(R)
 HT� C�C�+3
 �HP KCM_HE_COB�
 C� C�C�+1
 C�� 12
 HT� HOM_�A�
 � =.[19:1]
 �HP O��_C�C�
 ��A MAC_�TE(R2)
 ��A 4 0000H(R4)
 ��A -127(W)
��AK C� (R2)
 HT� =.[64:17]
 �PB �A�P
 B�
 � =.[64:33]
 C�M 1(R2)
 C�� 32
 ��� (S)
 C�M+ 2(R2)
 C�� 12
 ��M R
 �P� 400H(R)
 ��T+ 1(R1)
 ��K� ��AK(W)
 C��A 1(R9)
 �� ��C
�A�P ��A (W)
 C��A -4 0000H(R1)
 ��A (R1)
 �P�� 8
 C�T+ 1(R4)
 ��T+ 1(W)
 CTO�
 �� 1
O�M_��OKOM �� HOM_�A�
 �MH =8000 2B1D A461 02B2H
 B�M
 �MH �_�O��
 �� W
 B�
 �MH =8000 0000 0000 0005H
 C�� 25
 ��� =.25
 ��M ��N
 C�� 16
 ���� (W)
 C�� 16
 �� �����
 C�� 16
 ��� ��N
 �� ��N
 C�K =.25
 �� ��N+1
 C� 6(R3);A�PEC O��
 � =.[64:25]
 ��� -1(S)
 �� 6(R3)
 �� �A�BKA
�TEH�E_M� C�M HOM_KAH_M�
 �B �0(W)
 C� =[49]07H
 �B �A�BKA_M�(R);�EPEMOTKA
 �� HOM_�A�_M�
 ��A (R7)
: ��A #(R);�O�CK �A��A
 �HP O���KA_O�MEHA
 C��A -1(R7)
 ��PB HA����(R7)
 C� =[49]3FH;�A�� B�EPE�
�A�BKA_M�
 C�M HOM_�CT_M�
 C�� 56
 �� HOM_KAH_M�
 C�K HOM_KAH+1
 �� R5
 � =.[64:57]
 ��� (S)
 �� C�C�
 ��A C�C�(R3)
 ��A (R8)
 �� ��CK_O�MEHA
HA���� C� =02 80 0004 000000H!MAC_�TE
 �B �A�BKA_M�(R);�TEH�E METK� �A��A
 �HP O���KA_O�MEHA
 C� MAC_�TE+1
 �� KO�_�A�
 B�O� =1
 �� R9
 �� RA
 C� MAC_�TE
 �� A�P_O��
 �� R7
�EPE_MAC C� =02 80 0200 000000H
 ���� (R7)
 �B �A�BKA_M�(R);�TEH�E MACC�BA
 ��A -511(W)
 �HP O���KA_O�MEHA
: �� (S)
 C�T+ 1(R7)
 C�� 32
 C�K (S)
 B�M
 C�� 32
 C�K (S)
 ��K� #-3(W)
 �� KO�_�A�
 �� MAC_�TE-1(R9);�A��C� KCM
 ��K� �EPE_MAC(R9)
 C� KO�_�A�
 C�� 24
 ��� =02 80 0000 000000H!MAC_TEC
 �B �A�BKA_M�(R);�TEH�E �OH� C KCM
 �HP O���KA_O�MEHA
 ��A MAC_�TE(R7);CPABHEH�E KCM
: C�+ 1(R7)
 HT� MAC_TEC-1-MAC_�TE(R7)
: �PB #+1
 CTO� 8;KCM HE COB�A�A
 ��K� #-2(RA)
 C� (S)
 �� HOM_KAH
 C� KO�_�A�
 C�� 2;*4
 �MH �_�A�O
 C�K =1
 �� KO�_�A�
�EPE_O��_M�
 C� ���_�A�
 �MH� (R9)
 C�� 7
 C�K A�P_O��
 C�M ���_�A�
 �MH� (R9)
 C�K HOM_��O
 �B �A��C�(R7)
 �HP O���KA_O�MEHA
 C��A 1(R9)
 C� KO�_�A�
 B�� (R9)
 ��� �EPE_O��_M�
 �� BXO�
CTAPT_�BC
 C� ���_�A�
 �MH� (R9)
 C�� 7
 C�K A�P_O��
 C�M ���_�A�
 �MH� (R9)
 C�K HOM_��O
 �B �TEH�E(R7)
 �HP O���KA_O�MEHA
 C��A 1(R9)
 C� KO�_�A�
 B�� (R9)
 ��� CTAPT_�BC
 �� A�P_O��
 ��A (R8)
 C� KO�_�A�
 �MH ���_�A�
 C�� 7
 ��C
 �P�� -1
 C�T+ 1(R8)
 ��T+ 1(R9)
 �� 1
PA�METKA B� W
 �MH =L_��T
 C�K =1D 34 0094 000000H!MAC_TEC
 �� K�P�$(W)
 �� �_�A�
 C�� (W)
 �MH =L_��T
 C�K =1E 34 0094 000000H!MAC_TEC
 C��A 1(W)
 �� �_�A�
 �� K�P�$(W)
 C� �_�A�
 B�� (W)
 ��� PA�METKA
 �� �_�A�
 C� K�P�$(W)
 HT� =.43
 �� �_�A�
 �� K�P�$(W)
 C� =1A 54 0000 000000H!��C;C��TAT� CA
 �� K�P�$(W)
 C� �_����
 �MH �_�O�
 C�M �_�A�
 B� =1
 C�K PA�MEP_P�;�E�EH�E HA�E�O
 �MH �_�A�O
 �� KO�_�OP
 B�O� (S);814*19=15466 KO� �OPO�EK /200/
 �� ��C_�OP_�AM
 ��A (RC);C�ET��K �OPO�EK
PA�0 B� RC;TEK��A� �OPO�KA
 �MH �_�O�O;1/19
 B�M
 �MH �_�O��
 ��M W
 C�� 16
 ���� (W)
 �� PA�
 C�� 16
 �� �����
 C��M 8
 ��� =8000 80H;HET �E�EKTOB HA �OPO�KE
 ��M �����
 C�� 16
 �� ����ND�
 ��A (W)
 ��A MAC_TEC(R)
PA�1 C�� 1(W)
 C�� 24
 ��� =L_��O*9;���HA �AHH�X
 ��� ����ND�
 ��+ 1(R)
 ��A 1-/(L_��O-L_C�)//8(R5)
: ��A PA�M_KO�(R6)
 �P�� 8
 C�+ 1(R6)
 ��+ 1(R)
 ��K� #-2(R5)
 C�� -1
 ��+ 1(R);KCM
 BP� 1DH;�AC�
 C�� 20
 � =.[24:1]
 B�M RC;B���C�EH�E N �A��C�
 �MH �_�A�
 C�K� (W)
 C�� 24
 ��� (S)
 C�M �M�_P�
 C�P =0303 0303 0303 0303H
 ��� (S)
 �� C�C�+1;�OPM�POBAH�E KP
 C�� 32
 �E�
 � =1
 C�� 6
 C�M C�C�+1
 C�� 32
 �E�
 � =1
 C�� 7
 ��� (S)
 HT� =0D8H
 C�� 48
 C�M C�C�+1
 C�� 8
 ��� =[64:57]0D8H
 ��+ 1(R)
 B�
 ��� (S)
 ��+ 1(R)
 C� =[48:41]0D8H
 ��+ 1(R)
 C��A 1(W)
 C� �_�A�
 B�� (W)
 ��� PA�1
PA�2 ��A K�P�(R3);PA�METKA �OPO�K�
 �B �A�BKA(R)
 �HP �EPEA�PECA���
 C� �_�A�
 �MH =L_��T
 �� R
 ��A (W)
PA�3 C� MAC_TEC(W)
 ��A (R)
 HT� MAC_TEC(W)
 ��A (R)
 �� MAC_TEC(W);POC��C� ���EPA
 �HP �EPEA�PECA���
 C��A 1(W)
 B� R
 B�� (W)
 ��� PA�3
 ��A (RA)
 ��HP (RA)
 C��A 1(RC)
 C� KO�_�OP
 B�� (RC)
 ��� PA�0
 C� =T'��CK_BK�'
 �� METKA_TOMA
 C� ��C_�OP_�AM
 C�K =6;���HA �A�K�
 �� W;A�PEC HA�A�A ��PEKTOP��
 C� ��C�O_P�;�OC�ET ���H� METK� TOMA
 C��M 2;*4
 C�K� 127(W);�E�EH�E HA�E�O
 C�� 7
 �� ���_�A�;���HA METK� TOMA
 C�� 40
 ��� PA�MEP_P�;���HA OCHOBHO� �ACT� TOMA
 ��� =2700 0000 0000 0000H
 �� METKA_TOMA+3
 C� ��C_�OP_�AM
 C�� 48
 C�M KO�_�OP;HOMEP �EPBO� �A�ACHO� �OP
 C�� 24
 ��� (S)
 C�M PA�MEP_P�
 B� ���_�A�
 �� KOH_��OK;HOMEP ��OKA ����� METK�
 ��� (S)
 ��M METKA_TOMA+4
 C�� 48 ;��C�O BT
 ���� (W)
 �� METKA_TOMA+5
 C� �M�_P�
 �� METKA_TOMA+2
 �� METKA_TOMA(W)
 C� =.25
 �� METKA_TOMA+1(W);HOMEP HA�A��HO�O ��OKA
 C� PA�MEP_P�
 �� METKA_TOMA+2(W);���HA B�PT. TOMA
�A��C�_METK�
 C� =METKA_TOMA
 C�M ;OCHOBHA� METKA TOMA
 �B �A��C�(R7)
 �HP O���KA_O�MEHA
 C� =METKA_TOMA;����� METK� TOMA
 C�M KOH_��OK
 �B �A��C�(R7)
 �HP O���KA_O�MEHA
 �� BXO�
�EPEA�PECA���
 C� ��C_�OP_�AM
 B�O�
 �� W
: ��PB HET_PE�_�OP(W);�O�CK CBO� �OPO�K�
 C��A 1(W)
 �� ��C_�OP_�AM
 C� TA�_�E�-1(W)
 �HP #-2
 �� ��C_�OP_�AM
 C�� -1(W)
 C�K KO�_�OP
 �MH �_�O�O;1/19
 B�M
 �MH �_�O��
 ��M R
 C�� 16
 ���� (R)
 C��M 32
 �� ����ND�
 ��� PA�
 �� ��C_�OP_�AM
 �� TA�_�E�-1(W)
 C� �����
 ��� =[57]02H
 �� �����
 ��A K���(3);�E�EKTA��� �OPO�K�
 �B �A�BKA(R)
 �HP HE_���ETC�_CA
 C� =.57
 ��M �����
 C�� 16
 �� �����;A�PEC �A�ACHO� �OPO�K�
 �� PA�2
�TEH�E
 C�M =00 06 84 0083 000000H
 �B �OP_K�PO(R)
 �B ��CK_O�MEHA(R)
 �HP (R7)
 C� =���K
 �� R4
 C� K�A�
 ��M W
 �� R1;�A�A MACC�BA O�MEHA
�TE0 ��A -127(R2)
 C�
: �� (S)
 C�T+ 1(R4)
 ��T+ 1(R1)
 C�K (S)
 ��K� #-2(R2)
 HT�+ 1(R4)
 �HP KCM_HE_COB�
 C� N�A�
 HT�+ 2(R4);HOM TOMA; HOM ��OKA
 B�M
 C�K =.25
 ��M N�A�
 C�� 24
 �HP O��_C�C�
 ��K� �TE0(W)
 �� (R7)
�A��C�
 C�M =05 84 0083 000000H
 �B �OP_K�PO(R)
 C� K�A�
 ��M W;KO� �A��CE�
 �� R1;�A�A MACC�BA O�MEHA
 C� =���K
 �� R4;�A�A ���EPA KAHA�A
 C� ��A_�TE
 �PB �A�0
 C� =08 04 0000 000000H
 ���� L_K�P(R3)
 �� (R2)
 C� KKOM
 �� -1(R2)
�A�0 ��A -127(R2)
 C�
: �� (S)
 C�T+ 1(R1)
 ��T+ 1(R4)
 C�K (S)
 ��K� #-2(R2)
 ��+ 1(R4);KCM
 C� N�A�
 ��+ 2(R4);HOM TOMA; HOM ��OKA
 C�K =.25
 �� N�A�
 ��K� �A�0(W)
 �B ��CK_O�MEHA(R)
 C� ��A_�TE
 �PB (R7)
 C� =���K
 �� R4
 C� K�A�
 �� W
KCM C�
 ��A -127(R3)
: �� (S)
 C�T+ 1(R4)
 C�K (S)
 ��K� #-1(R3)
 HT�+ 3(R4)
 �HP O���KA_O�MEHA
 ��K� KCM(W)
 �� (R7)
�OP_K�PO
 C�M HOM_KAH;�OPM�POBAH�E �A�� KAHA�A
 �MH =L_KH
 ��C
 ��A ���EP(RB)
 ��A (RB)
 ��A ����N-KH(R1)
 ��A (RB)
 ��A KAH_�PO-KH(R2)
 C�� -1
 ��+ 1(R1)
 C� HOM_�CT
 �� R6
 C�� 56
 �� HOM_KAH
 C�K HOM_KAH+1
 �� R5;A�PEC M�K
 � =.[64:57]
 �� �CTP
 ��� R3(R2)
 ��� (S)
 C�K =���K-L_��O
 �� KKOM
 C� =1
 B� ���_�A�
 �� W
 ��M K�A�
 �� R4;HA�A��H�� ��OK
 C�� 24
 C�M �M�_P�
 C�P =0303 0303 0303 0303H
 ��� (S)
 �� N�A�
�OP0 C�� (R4)
 C��A 1(R4)
 �MH �_���O;1/190
 B�M ;����H�
 �MH �_�O��;*19
 �� HOM_�O�
 B�
 �MH �_�A��;*10
 C�� 8
 C�K =100H
 ��M HOM_�A�
 B� �_���;MAX ����H�P
 ��P HEBEP_��A�
 C� �_���
 C�� 16;����H�P
 ��� HOM_�O�
 C�� 16
 ��� HOM_�A�
 �� (R1)
 C�� 16
 �� (S)
 HT� -1(R1)
 C�� 32
 �PB HET_�CT
 C� =07 64 0000 000000H
 ��� �CTP
 ���� (R1)
 ��+ 1(R2)
 �� L_K�P-1(R2);KK �TE
 C��A 1(R1)
HET_�CT C� =31 54 0000 000000H
 ��� �CTP
 ���� (R1)
 ��+ 1(R2)
 ��M L_K�P-1(R2);KK �TE
 ��+ 1(R1)
 C� =08 04 0000 000000H
 ���� -1(R2)
 ��+ 1(R2)
 C�K =L_K�P
 �� L_K�P-1(R2);KK �TE
 C� KKOM;KOM=��/C�
 C�K =L_��O
 �� KKOM
 ��+ 1(R2)
 C�K =.49
 �� L_K�P-1(R2);KK �TE
 ��K� �OP0(W)
 HT� =.43
 �� L_K�P-1(R2);KK �TE
 C� KKOM
 HT� =.43
 �� -1(R2)
 ��A -7(R8)
 �� (R)
�A�BKA
 ��A -7(R8);�OPM�P�ET H�C
 C� HOM_�CT
 �� R6
 C�� 56
 �� HOM_KAH
 C�K HOM_KAH+1
 �� R5
 � =.[64:57]
 �� �CTP
 ��� W(R3)
: C� (W)
 � =.[56:1]
 ��� �CTP
 ��+ 1(W)
 � =.43
 �HP #-2
��CK_O�MEHA
 B� R3
 �B ���_�PE(W)
 BP� 280H(R5)
 �� �CK
 BP� 284H(R5)
 � =.[19:1]
 �� ACK
 BP� 286H(R5)
 �� CCK
 C�� 1
 � =7
 B�M
 �� (S)
 �PB �EPEK_XAP
 BP� 686H(R5);ECT� TP�-A
 C�� 24
 � =0FFH
 �� HOM_KAH
 C�M HOM_KAH+1
 C�� 56
 B�O� (S);CM=HOM_�CT
 �� ��CK_O�MEHA
�EPEK_XAP ��A X0(W);XAP=0
 �� AHA���_CCK
 ��A X1(W);XAP=1
 �� AHA���_CCK
: �� O��_O�M;XAP=2 OTKA� KAHA�A
: �� O��_O�M;XAP=3 O� A�PECA B�
: �� O��_O�M;XAP=4 B� HE HA��EHO
: BP� 686H(R5);XAP=5 B� �AH=50 00 0A
 �� ����
 CTO� 6;XAP=6 O��� �TEH�� O��
 �� BXO�
 CTO� 7;XAP=7 �EPEXO� B KAHA�E
 �� BXO�
AHA���_CCK �� (W)
 ��A (R4);���HA
 C� CCK
 C���+ 1(W)
 HT� (R3)
 � =.[64:57]
 �HP O�_HOM_�CT
: B�
 HT�+ 1(W)
 �+ 1(W)
 �� -2(W)
 �PB
 ��K� #-2(R4)
O��_O�M BP� 680H(R5)
 C� ACK
 ��� =08 04 0000 000000H
 �� K�KP+2
 C� K��C;�TO�HEH�E COCTO�H��
 � =.[56:1]
 ��� �CTP
 �� K��C
 C� =K��C
 �B ���_�PE(W)
 BP� 686H(R5)
 C� ��C
 HT� =53H
 � =0FFH
 �PB KOPPEK���
 C� K�OB(R6)
 C�K =.17
 �� K�OB(R6)
 ��K� ��CK_O�MEHA(R8)
 C�K =.33
 �� K�OB(R6)
 ��A �CK(W)
 �� A���C
 ��A (R4)
 �P�� 5
 C�+ 1(W)
 ��+ 1(4)
 B� R4
 �� A���C
 HT� =���_CTA+300
 �PB MHO�O_O���OK
 C� ��C
 � =.[64:61]
 �HP TPE��ETC�_BME�
 �� �CTP
OKOT C� =1
 �� (R)
KOPPEK���
 C� �CK
 � =.48
 �HP KOPT+1;ECT� TE� !!
 C� K�OB(R6);C�ET��K KOPPEK���
 C�K =.49
 �� K�OB(R6)
 C� �CK
 � =.[19:1];A�PEC ���EPA
 C�� 3
 C�M ��C+2
 C�� 48
 B�M
 C�� 48
 B�O� (S)
 C�K (S)
 ��A -2(R8)
� C��M 2(R8)
 C�� 3
 C� ��C+2
 C��� -24
 � =0FFH
 C��M 2(R8)
 C�K -2(S)
 C�� 3
 ��M W
 C��� -56
 HT� (W)
 ��M (W)
 ��K� �(R8)
 C� �CK
 � =.43
 �PB (R);KOMAH�A �OC�E�H�� B �E�O�KE
 C� K�KP
 � =.[56:1]
 ��� �CTP
 �� K�KP
 C� =K�KP
 ��A ��CK_O�MEHA+1(W)
 �� ���_�PE
KOPT
 BP� 680H(R5)
: C� �CK
 C�M ACK;�OP �PO�PAMM� �TEH�� �E� TE�OB
 �� W;A�PEC KOMAH��
 ��� =08 04 0000 000000H;BO�BPAT B �E�O�K�
 B�M R3;A�PEC �E�O�K�
 B�M R;A�PEC BO�BPATA
 C�M -1(W)
 � =0FF FF 0B 0000 FFFFFFH;�E� TE�OB � �E�O�K�
 ��� =00 00 30 0094 000000H;���HA �E� TE�OB
 �� K�KPT+2
 � =.[19:1];�A�A ���EPA
 C�M -3(W);�O�CK �O ��EHT���KATOP�
 �� K�KPT
 ��A K�KPT(R3)
 �B ��CK_O�MEHA(R)
 ��M R4;KOT
 �� W;�A�A ���EPA
 ��� R3(W)
 ��A -16(R8)
: ��A -64(R)
PAC� C�+ 1(W);PAC�AKOBKA ���EPA C TE�AM�
 C�� 64(R)
 C�M (W)
 C�� (R)
 ��� (S)
 C�M (W)
 C�� 12(R)
 � =03F0H
 ��C
 �PT
 C� (S)
 ��T+ 1(R3)
 C��A 8(R)
 ��HP PAC�(R)
 C��A 1(W)
 ��K� PAC�-1(R8)
 C� (S);BOCCTAHOB�EH�E
 ��M R
 ��M R3
 ��M K�KPT;KOMAH�A BO�BPATA B �PEPBAHHOE MECTO
 ��HP OKOT(R4);HE �PO���, A XOTE��
 � =.43
 �PB (R);�OC�E�H�� KOMAH�A
 C� =K�KPT;BO�BPAT B �E�O�K�
 ��A ��CK_O�MEHA+1(W)
 �� ���_�PE
MHO�O_O���OK C� =34H
 �� BXO�
TPE��ETC�_BME� C� =30H
 �� BXO�
HE_���ETC�_CA C� =9H
 �� BXO�
HET_PE�_�OP C� =28H
 �� BXO�
O�_HOM_�CT C� =27H
 �� BXO�
O��_C�C� C� =31H
 �� BXO�
KCM_HE_COB� C� =32H
 �� BXO�
O���KA_O�MEHA C� =33H
 �� BXO�
TOM_HE_MO� C� =35H
 �� BXO�
HEBEP_��A� C� =39H
 �� BXO�
HA�O_�OB BP� 681H(R5);HO�� KAHA�A
 C� K�OB(R6)
 C�K =1
 �� K�OB(R6)
 C� ACK
 B� =1
 ��A ��CK_O�MEHA+1(W)
 �� ���_�PE
HET_O�� BP� 686H(R5)
 C�
 �� �CTP
 �� (R)
TECT_M�
 C� �_�A�
 �MH �_�O�
 C�M O�EPE��+3(R1)
 C�� 20
 � =.[16:1]
 �MH (S);10*19= 190
 C�M O�EPE��+3(R1)
 C�� 12
 � =0FFH
 �MH �_�A�
 C�K (S)
 C�� 12
 C�M O�EPE��+3(R1)
 � =0FFFF FFFF 0000 0FFFH
 ��� (S)
 �� C�C�+3(R1)
 ��K� TECT_M�(R1)
 BP� 1DH;�AC�
 �� X
HA�_�POCM ��H (S)
 ��A -3(R9)
C�E�_�A�B C� =0EB6D B6DB EB6D B6DBH
 ��A MAC_�TE(W)
 �P�� L_��O*L_K�A-1
 ��+ 1(W)
 C� C�C�+3(R9);PAC�AKOBKA �A�BK�
 � =0FFFH
 �PB K�
 ��� (S)
 C�M C�C�+3(R9)
 C�� 4
 B�M
 ��M HOM_KAH
 C�� 4
 B�M
 ��M HOM_�CT
 C�� 4
 B�M
 ��C
 ��M �M�_P�
 C�� 8
 B�M
 �� ���_�A�
 B� =1
 C�� 12
 ��� =0FFFH
 C�K C�C�+3(R9)
 ��M C�C�+3(R9)
 C�� 4
 B�M
 ��A �A��C�(W)
 ��M R
: ��HP #+1(R)
 ��A �TEH�E(W)
 C�� 4
 B�M
 ��M ��A_�TE
 C�� 4
 B�M
 ��M R
 C�� 20
 C� =MAC_�TE
 B�M
: ��PB #+1(R)
 �B RAN(R);HOMEP ��OKA OT RAN
 ��A (W)
 �B (R7)
K� ��K� C�E�_�A�B(R9)
 C� (S)
 �HP HA�_�POCM
 ��A -3(W)
: C�� 16
 C�M K�OB+3(W)
 C�� 32
 � =.[16:1]
 ��� (S)
 ��K� #-2(W)
 �� BXO�
�TEH�E_METK�
 C� =1
 �� ���_�A�
 C� =METKA_TOMA
 C�M ;�TEH�E 0-��OKA
 �B �TEH�E(R7)
 �HP O���KA_O�MEHA
 C� METKA_TOMA
 HT� =T'��CK_BK�'
 �HP TOM_HE_MO�
 C� METKA_TOMA+3
 C�� 40
 � =0FFH
 �� ���_�A�;PA�MEP METK� TOMA
 �� HA�_��OK
 C� =METKA_TOMA
 C�M ;�TEH�E METK� TOMA(�����=257A7H)
 �B �TEH�E(R7)
 �HP O���KA_O�MEHA
 C� METKA_TOMA+4
 � =.[19:1]
 �� KOH_��OK;KO��� METK�
 C� METKA_TOMA+5
 �� W
 C��A METKA_TOMA(W);�A�A ��PEKTOP��
 C�� 48
 B�O� =1
 �� R;MAX ��C�O BT B ��PEKTOP��
 ��� R1(W)
 C��A 4(W)
 ��A (R3)
CKAH C��A 4(R1);�O�C�ET ���H� ��PEKTOP��
 C� (R1)
 �PB (RA)
 HT� �M�_P�
 C�M 1(R1)
 HT� �M�_P�+1
 C�� 32;24!!
 ��� (S)
: �HP #+1
 ��� R3(R1);A�PEC COB�AB�E�O �MEH� BT
 ��K� CKAH(R)
 �� (RA)
PEMOHT
 C� HOM_��O
 �MH �_�A�O;1/10
 �� RC;HOMEP �OPO�K�
 �MH �_�A�;HA� HOMEP ��OKA HA �OPO�KE
 �� HOM_��O
 B� RC
 �MH �_�O�O;1/19
 B�M
 �MH �_�O��
 ��M R
 C�� 16
 ���� (R)
 C�M METKA_TOMA+4;B MA� ����
 C��M 24
 � =.[19:1]
 ��M KO�_�OP;N �EPBO� �A�ACHO� �OPO�K�
 C�� 48
 �� ��C_�OP_�AM
 B�O� =1
 �� W
 ��A TA�_�E�(R)
�O�CK_�OP C�+ 1(R)
 HT� -1(S);����
 C�� 32
: �HP #+1
 �� -1(R)
 ��K� �O�CK_�OP(W)
 ��A (R9)
 C� =1
 ��M ���_�A�
��P_�OP C�� (R9)
 C�� 7
 C�K =MAC_�TE
 C��M (R9)
 C�K HOM_��O
 �B �TEH�E(R7)
 �� CTEK+10(R9)
 C��A 1(R9)
 C� �_�A�
 B�� (R9)
 ��� ��P_�OP
 ��A (R9)
 �B PA�0(RA)
BOC_�OP C� CTEK+10(R9)
 �HP KOH_BOC
 C�� (R9)
 C�� 7
 C�K =MAC_�TE
 C��M (R9)
 C�K HOM_��O
 �B �A��C�(R7)
 �HP O���KA_O�MEHA
KOH_BOC C��A 1(R9)
 C� �_�A�
 B�� (R9)
 ��� BOC_�OP
 �� �A��C�_METK�
CO�_P�
 C� =3;KOT=3
 ��HP BXO�(R3)
�O�CK_�PA� C� 1(W)
 � =.[19:1]
 �PB B_KOHE�
 �� PA�
 C� HA�_��OK
 C�K PA�MEP_P�
 B�O� PA�
 ��P ECT�_�PA�
 C� 2(W)
 � =.[19:1]
 C�K PA�
 �� HA�_��OK
 C��A 4(W)
 ��K� �O�CK_�PA�(R)
KOT1 C� =1;HET MECTA ��� O��CATE�� �A��A
 �� BXO�
ECT�_�PA� C��A -1(R1);�OC�E�H�� O��CATE��
 ��� R(W)
 B�� R(R1);���HA �EPE��C�
: C�+ -1(R1)
 �� 5(R1)
 ��K� #-1(R)
B_KOHE� C� �M�_P�
 �� (W)
 C� �M�_P�+1
 � =.[64:33]
 ��� =.25;KO���=1
 ��� HA�_��OK
 �� 1(W)
 C� PA�MEP_P�
 �� 2(W)
 C� HA�_��OK
 C�K PA�MEP_P�
 B� KOH_��OK
 �MH �A��C�_METK�
 C� =2;HET �POCTPAHCTBA ��� BT
 �� BXO�
�CK_P�
 ��PB KOT1(R3);�M� HE HA��EHO
 C��A -5(R1)
 B��O� R3(R1)
 ���� #+3(R1)
: C� 4(R3)
 ��+ 1(R3)
 ��K� #-1(R1)
: C�
 �P�� 3;POC��C� XBOCTA
 ��+ 1(R3)
 �� �A��C�_METK�
�CT �P�;B���C�EH�E KO� �A��CE� HA �OPO�KE
 C� =59+11+7+49+L_��O*9+7;�O�H�� O�'EM �A��C�
 KOP 434H
 C�M O_�OP
 B� =92+13+7+49+11+7;���HA HA
 KOP 434H
 �E� (S)
 �E�� 52
 �� �_�A�
 �� ���_�A�
 HT� =.64
 �� �_�A��
 B�
 �B �PEO�(W)
 �� �_�A�O
 C� �_�O�
 HT� =.64
 �� �_�O��
 B�
 �B �PEO�(W)
 �� �_�O�O
 C� �_�O�;��C�O �A��CE� HA ����H�PE
 �MH �_�A�
 �B �PEO�(W)
 �� �_���O
 C� =.[40:33]
 ��A -31(W)
: �P� 40H+31(W);�CTAHOBKA �P���CK�
 C�K =0000 0100 0000 0100H
 ��K� #-1(W)
 �P� 22H;�CTAHOBKA PMC
 C� =.[64:33]
 �P� 29H;�CTAHOBKA PC�O
 C� =���_CTA
 �� A���C
 C� =1200H;�O� � TT
 �P �C1
 C� =[48:33]0C002H
 �P� 26H;�CTAHOBKA MACK�
 C� HOM_KAH
 �MH =L_KH
 ��C
 ��A ���EP(RB)
 C� HOM_KAH
�0 C�M =.44;O�H��EH�E KOHTP
 �� (S)
 C��
 �P� 24H
 C�
 �P� 24H
 ��A 32(R5)
CH�_�M
 C�� =08 40 0000 000000H;�EPEXO� B KAHA�E
 C��A -8(R5)
 �P� 484H(R5)
 ��A -99(W)
: �� ;�A�EP�KA
 ��K� #(W)
 C�
 ��A -7(W)
: ��A (R5);POC��C� M�K
 �P� 80H+7(W)
 ��K� #-1(W)
 BP� 686H(R5);O�H��EH�E KAHA�A
 ��HP CH�_�M(R5)
 ��A K�CT(R3)
 �� �A�BKA
RAN C� �_���
 �MH �_�O�
 �MH �_�A�
 HT� =.64
 B�M
 �B �PEO�(W)
 C�M X
 C�� 4
 HT� X
 C��M 11
 HT� (S)
 � =.[52:1]
 �� X
 �MH (S);1/808*19*10= 153 520 /200/
 B�
 �MH (S);808*19*10= 153 520 /200/
 �� (R)
�PEO� �P� 20H
 KOP 434H
 C�M =�'1.0'
 �E� -1(S)
 � =.[52:1]
 ��M PA�
 C�K =.[64:54]
 C�M PA�
 C��� (S)
 C�K =8000 0000 0000 0001H
 �P� 230H
 �� (W)
���_�PE B�T
 �P� 484H(R5);��CK KAHA�A
���� BP� 24H
 C�M =[36]11H
 �� HOM_KAH
 C��
 � (S)
 �PB ����
 � =.36
 �PB (W)
: CTO� 0777H;
 �� #
 H��CT �C�,EC��
 EC�� 1=0
���� C� =.19;300 M���CEK.
 �P� 1EH;TA�MEP
 ��P 4;PA�P BHE_�PE
 C�
: C�K =1;������ TECT
 �� #
BHE_�PE C� =1200H;�O�,TT
 �P �C1
 BP� 27H;�PB�
 C�P =[48:33]0C002H
 HE�
 �PB ����
 ��C
 �� #
: �� KOEC
: CTO� 771H;�CEC
 �� BXO�
: CTO� 0FFFH;TA�MEP
 �� ����
KOEC
 BP� 24H
 C�� 24
 � MAC_KAH
 �PB O�_HOM_�CT
 HE�
 B� =1
 �� HOM_KAH
 ��C
 �� HOM_KAH+1
 ��A (R5);A�PEC M�K
 �MH =L_KH
 ��C
 ��A ���EP(RB)
 C� =1200H;�O� � TT
 �P �C1
 �� (W)
�KCTPAKO�
 �� PA�;�TO CM
 B� S
 �� �O�_��P+16
 B� W
 �� �O�_��P+15
 ��A �O�_��P(S)
 ��A -12(W)
 �P� 230H
 BP �C3
 BPM �C7
: B�M 13(W)
 ��K� #(W)
 ��A -6(W)
 C�M �O�_��P+16;CTEK �O���OBATE��
 �� S
 C� PA�;�TO CM
: ��M A�P_O��+6(W);�EPE��C� �APAMETPOB B��OBA
 ��K� #(W)
 ��A CTEK(S)
 BP �C2;�C� A�PEC �KC
 ��C
 �� #+1
: �� �K�
: ��A �A��C�(W);�C�=1
 �� �K0
: ��A �TEH�E(W);�C�=2
�K0 C� A�P_O��
 C�M HOM_��O
 ��A BO�_�KC(R7)
 �� (W)
�K� �B �CT(R)
BO�_�KC �� PA�;KO� OTBETA
 C� �O�_��P;�C3 - KOPPEK��� A�PECA BO�BPATA
 �P �C3
 C� �O�_��P+1;�C7
 �P �C7
 ��A 13(W)
 ��A �O�_��P+15(S)
 C� (S)
: ��M (W)
 C��A -1(W)
 ��HP #-1(W)
 �� �O�_��P+16;�P15
 ��A (S)
 �� �O�_��P+15;�P14
 ��A (W)
 �P� 30H
 C� PA�;KO� OTBETA
 B�X
 BCE
 ��TEP
METKA_TOMA
 K��OK ��CK�
 ��H��
