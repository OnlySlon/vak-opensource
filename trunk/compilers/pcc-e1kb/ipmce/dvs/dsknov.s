                MO����  'DISK_IO'               
TEXT#           CEK���  3E011H,�20,H�A�,�PE�,�KOM
DISK:                                           
                �P�     230H                    
                B�M     W                       
                ��A     -12(W)                  
SR                                              
                B�M     R1+12(W)                
                ��K�    SR(W)                   
                C�M     7(R1)                   
                ��      KOT                     
                ��A     -7(W)                   
                ��A     HOMKAH(R2)              
��AP                                            
                ��A     (R1)                    
                C�      7(W)                    
                ��+     -1(R2)                  
                ��K�    ��AP(W)                 
                B�      S                       
                ��      CTEK                    
                ��      KOT                     
                ��      #+1                     
:               ��      �K�                     
:               ��A     �A��C�(W)               ; �C�=1
                ��      �K0                     
:               ��A     �TEH�E(W)               ; �C�=2
�K0             C�      A�P_O��                 
                C�M     HOM_��O                 
                ��      (W)                     
A�P_O��         �AM                             
HOM_��O         �AM                             
��A_�TE         �AM                             
���_�A�         �AM                             
HOM_�AK         �AM                             
HOM_�CT         �AM                             
HOM_KAH         �AM                             
                KOH�    038000000 00000000H     
                KOH�    0D8000000 00000008H     
                KOH�    058000000 00000010H     
                KOH�    080000000 00000018H     
R1              �KB     1                       
R2              �KB     2                       
R3              �KB     3                       
R4              �KB     4                       
R5              �KB     5                       
R6              �KB     6                       
R8              �KB     8                       
RB              �KB     11                      
R               �KB     13                      
W               �KB     14                      
S               �KB     15                      
���EP           �KB     40000H - 6000           
�CK             �AM                             
CCK             �AM                             
��C             �AM     3                       
HOM_�O�         �AM                             
HOM_�A�         �AM                             
X0              KOH�    8300 0000 0FFF FFFFH    ; ��� XAP=0
                KOH�    [25]00 08 04 0000H!HET_O��
                KOH�    [25]00 FF FF 1F90H      
                KOH�    [25]00 4A 04 0010H!HA�O_�OB
                KOH�    [25]00 FF FF 1F90H      
X1              KOH�    8400 0000 0FFF FFFEH    ; ��� XAP=1
                KOH�    [33]000C 0000H!HET_O��  ; KB
                KOH�    [33]00FF 1F90H          
                KOH�    [33]004E 0010H!HA�O_�OB ; MKBC
                KOH�    [33]00FF 1F90H          
                KOH�    [33]0008 0000H!HET_O��  ; KK OKK=1
                KOH�    [33]00FF 1F90H          
K��C            KOH�    00 04 00 0003 000000H!��C
�TEH�E          C�M     =00 06 84 0083 000000H  
                �B      �OP_K�PO(R)             
                �B      ��CK_O�MEHA(R)          
                ��A     (RB)                    
                ��A     ���K(R4)                
                C�      K�A�(RB)                
                ��M     W                       
                ��      R1                      ; �A�A MACC�BA O�MEHA
�TE0            ��A     -127(R2)                
                C��                             
:               ��      (S)                     
                C�T+    1(R4)                   
                ��T+    1(R1)                   
                C�K     (S)                     
                ��K�    #-2(R2)                 
                HT�+    1(R4)                   
                �HP     KCM_HE_COB�             
                C�      N�A�(RB)                
                HT�+    2(R4)                   ; HOM TOMA; HOM ��OKA
                C��     24                      
                ��                              ; �HP O��_C�C�
                C�      N�A�(RB)                
                C�K     =.25                    
                ��      N�A�(RB)                
                ��K�    �TE0(W)                 
                C��                             
                ��      BO�BPAT                 
�A��C�          C�M     =00 05 84 0083 000000H  
                �B      �OP_K�PO(R)             
                C�      K�A�(RB)                
                ��M     W                       ; KO� �A��CE�
                ��      R1                      ; �A�A MACC�BA O�MEHA
                ��A     (RB)                    
                ��A     ���K(R4)                ; �A�A ���EPA KAHA�A
                C�      ��A_�TE                 
                �PB     �A�0                    
                C�      =00 08 04 0000 000000H  
                ����    128(R3)                 
                ��      (R2)                    
                C�      KKOM(RB)                
                ��      -1(R2)                  
�A�0            ��A     -127(R2)                
                C��                             
:               ��      (S)                     
                C�T+    1(R1)                   
                ��T+    1(R4)                   
                C�K     (S)                     
                ��K�    #-2(R2)                 
                ��+     1(R4)                   ; KCM
                C�      N�A�(RB)                
                ��+     2(R4)                   ; HOM TOMA; HOM ��OKA
                C�K     =.25                    
                ��      N�A�(RB)                
                ��K�    �A�0(W)                 
                �B      ��CK_O�MEHA(R)          
                C�      ��A_�TE                 
                �PB     BO�BPAT                 
                ��A     (RB)                    
                ��A     ���K(R4)                
                C�      K�A�(RB)                
                ��      W                       
KCM             C��                             
                ��A     -127(R3)                
:               ��      (S)                     
                C�T+    1(R4)                   
                C�K     (S)                     
                ��K�    #-1(R3)                 
                HT�+    3(R4)                   
                �HP     O���KA_O�MEHA           
                ��K�    KCM(W)                  
                ��      BO�BPAT                 
���K            �KB     0                       ; CTP�KT�PA ��K
����N           �KB     ���K+131*32             
KKOM            �KB     ����N                   
MKAH_�PO        �KB     ����N+32+6              
�CTP            �KB     MKAH_�PO+258            
N�A�            �KB     �CTP+1                  
K�A�            �KB     N�A�+1                  
�OP_K�PO        C�M     HOM_KAH                 ; �OP�M�POBAH�E �A�� KAHA�A
                �MH     =4435                   
                ��C                             
                ��A     ���EP(RB)               
                ��A     (RB)                    
                ��A     ����N+1(R1)             
                ��A     (RB)                    
                ��A     MKAH_�PO(R2)            
                C�      HOM_�CT                 
                ��      R6                      
                C��     56                      
                ��      HOM_KAH                 
                C�K     HOM_KAH+1               
                ��      R5                      ; A�PEC M�K
                �       =.[64:57]               
                ��      �CTP(RB)                
                ���     R3(R2)                  
                ���     (S)                     
                C�K�    ���K-83H(RB)            
                ��      KKOM(RB)                
                C�      =1                      
                B�      ���_�A�                 
                ��      W                       
                ��M     K�A�(RB)                
                ��      R4                      ; HA�A��H�� ��OK
                C��     24                      
                C�M     HOM_�AK                 
                C��     48                      
                ���     (S)                     
                ��      N�A�(RB)                
�OP0            C��     (R4)                    
                C��A    1(R4)                   
                �MH     =8000 158E D230 8159H   ; R1/190
                B�M                             ; ����H�
                �MH     =8000 0000 0000 0013H   
                ��      HOM_�O�                 
                B�                              
                �MH     =8000 0000 0000 0A00H   ; 256*10
                C�K     =100H                   
                ��M     HOM_�A�                 
                B�      =327H                   
                ���     HEBP_��A�               
                C�      =327H                   
                C��     16                      ; ����H�P
                ���     HOM_�O�                 
                C��     16                      
                ���     HOM_�A�                 
                ��      (R1)                    
                C��     16                      
                ��      (S)                     
                HT�     -1(R1)                  
                C��     32                      
                �PB     HET_�CT                 
                C�      =00 07 64 0000 000000H  
                ���     �CTP(RB)                
                ����    (R1)                    
                ��+     1(R2)                   
                ��      127(R2)                 ; KK �TE
                C��A    1(R1)                   
HET_�CT         C�      =00 31 54 0000 000000H  
                ���     �CTP(RB)                
                ����    (R1)                    
                ��+     1(R2)                   
                ��M     127(R2)                 ; KK �TE
                ��+     1(R1)                   
                C�      =00 08 04 0000 000000H  
                ���     �CTP(RB)                
                ����    -1(R2)                  
                ��+     1(R2)                   
                C�K     =128                    
                ��      127(R2)                 ; KK �TE
                C�      KKOM(RB)                ; KOM=��/C�
                C�K     =83H                    
                ��      KKOM(RB)                
                ��+     1(R2)                   
                C�K     =.49                    
                ��      127(R2)                 ; KK �TE
                ��K�    �OP0(W)                 
                HT�     =.43                    
                ��      127(R2)                 ; KK �TE
                C�      KKOM(RB)                
                HT�     =.43                    
                ��      -1(R2)                  
                ��A     -7(R8)                  
                ��      (R)                     
��CK_O�MEHA     B�      R3                      
                �B      ���_�PE(W)              
                BP�     286H(R5)                
                ��      CCK                     
                C��     1                       
                �       =7                      
                B�M                             
                ��      (S)                     
                �PB     �EPEK_XAP               
                BP�     686H(R5)                ; ECT� TP�-A
                C��     24                      
                �       =0FFH                   
                ��      KOT                     
                ��      ��CK_O�MEHA             
�EPEK_XAP       ��A     X0(W)                   ; XAP=0
                ��      AHA���_CCK              
                ��A     X1(W)                   ; XAP=1
                ��      AHA���_CCK              
:               ��      O��_O�M                 ; XAP=2 OTKA� KAHA�A
:               ��      O��_O�M                 ; XAP=3 O� A�PECA B�
:               ��      O��_O�M                 ; XAP=4 B� HE HA��EHO
:               BP�     686H(R5)                ; XAP=5 B� �AH=50 00 0A
                ��      ����                    
                CTO�    6                       ; XAP=6 O��� �TEH�� O��
                ��      #                       
                CTO�    7                       ; XAP=7 �EPEXO� B KAHA�E
                ��      #                       
AHA���_CCK      ��      (W)                     
                ��A     (R4)                    ; ���HA
                C�      CCK                     
                C���+   1(W)                    
                HT�     (R3)                    
                �       =.[64:57]               
                �HP     O�_HOM_�CT              
:               B�                              
                HT�+    1(W)                    
                �+      1(W)                    
                ��      -2(W)                   
                �PB                             
                ��K�    #-2(R4)                 
O��_O�M         BP�     680H(R5)                
                ��      �CK                     
                C�      K��C                    ; �TO�HEH�E COCTO�H��
                �       =.[56:1]                
                ���     �CTP(RB)                
                ��      K��C                    
                C��     K��C                    
                �B      ���_�PE(W)              
                BP�     686H(R5)                
                ��K�    ��CK_O�MEHA(R8)         
                C�      =1                      
                ��      BO�BPAT                 
O�_HOM_�CT      C��     2                       
                ��      BO�BPAT                 
O��_C�C�        C��     3                       
                ��      BO�BPAT                 
KCM_HE_COB�     C��     4                       
                ��      BO�BPAT                 
O���KA_O�MEHA   C��     5                       
                ��      BO�BPAT                 
TOM_HE_MO�      C��     6                       
                ��      BO�BPAT                 
HEBP_��A�       C��     7                       
                ��      BO�BPAT                 
HET_O��         BP�     686H(R5)                
                ��      (R)                     
HA�O_�OB        BP�     681H(R5)                ; HO�� KAHA�A
                BP�     284H(R5)                
                �       =.[23:1]                
                B�      =1                      
                ��A     ��CK_O�MEHA+1(W)        
���_�PE         B�T                             
                �P�     484H(R5)                ; ��CK KAHA�A
����            BP�     24H                     
                C�M     =[36]11H                
                ��      HOM_KAH                 
                C��                             
                �       (S)                     
                �PB     ����                    
                �       =.36                    
                �PB     (W)                     
:               CTO�    0FFFH                   ; ECT� �CEC
                ��      #                       
�K�             C�      =.44                    ; O�H��EH�E KOHTP
                ��      HOM_KAH                 
                C��                             
                �P�     24H                     
                C��                             
                �P�     24H                     
                ��A     32(W)                   
CH�_�M          C��     =00 08 04 0000 000000H  ; �EPEXO� B KAHA�E
                C��A    -8(W)                   
                �P�     484H(W)                 
                ��A     -99(R)                  
:               ��                              ; �A�EP�KA
                ��K�    #(R)                    
                BP�     686H(W)                 ; O�H��EH�E
                ��HP    CH�_�M(W)               
                C��                             
BO�BPAT         ��      KOT                     
                ��      CTEK                    
                ��A     (S)                     
                ��A     13(W)                   
                C�      (S)                     
                �P�     200H                    
RR              ��M     (W)                     
                C��A    -1(W)                   
                ��HP    RR(W)                   
                ��      W                       
                ���     S(R1)                   
                C��A    -1(S)                   
                C�      KOT                     
                ��      (W)                     
KOT             �AM                             
                ��TEP                           
CTEK            �AM                             
                ��H��                           
