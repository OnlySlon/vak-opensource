set title "Antenna gain vs bandwidth, band 21 MHz, free space"
set nokey #bottom right

set terminal png monochrome
set output "helquad-eff-bw.png"

#set terminal postscript eps enhanced monochrome "Times-Roman" 24
#set output "helquad-eff-bw.eps"
#set size 2,2

set xlabel "Gain relative to ideal dipole, %"
set ylabel "Bandwidth, kHz"
set logscale y

eff(x) = 100 * exp(x * 0.2302585092994045684)

set label "Dipole"		at 2+eff(-0.10),	1540
set label "Delta"		at 2+eff( 0.76),	1372
set label "Quad"		at 2+eff( 1.09),	1469
#set label "Loop"		at 2+eff( 1.38),	1640
#set label "Mag.loop 2"		at -14+eff(-0.87),	225
set label "Mag.loop 1.5"	at 2+eff(-0.96),	87
set label "Mag.loop 1.2"	at 2+eff(-1.33),	48
set label "Mag.loop 1"		at 2+eff(-1.9),		30

#set label "Hel.quad 2-16"  	at 2+eff(-0.32),	360
#set label "Hel.quad 2-24"	at 2+eff(-0.28),	394
set label "Hel.quad 1.5-16"	at -19+eff(-0.71),	175
set label "Hel.quad 1.5-24"	at -19+eff(-0.66),	196
set label "Hel.quad 1.2-16"	at -19+eff(-1.17),	100
set label "Hel.quad 1.2-24"	at -19+eff(-1.01),	114
set label "Hel.quad 1-16"  	at -16+eff(-1.82),	62
set label "Hel.quad 1-24"  	at -16+eff(-1.55),	74

# PNG point types:
# 1 - diamond
# 2 - plus
# 3 - box
# 4 - X
# 5 - triangle
# 6 - star
plot [50:140] [20:2000] '-' using (eff($1)):2 with points pointtype 1 ps 2,\
	'-' using (eff($1)):2 with points pointtype 6 ps 1.5
	-0.10	1540	73	0.9681	# ������
	0.76	1372	119	1.0707	# ������
	1.09	1469	127	1.058	# �������
#	1.38	1640	138	1.04	# ������
#	-0.87	225	7.4	0	# ����.����� 2 �
	-0.96	87	2.4	0	# ����.����� 1.5 �
	-1.33	48	1.1	0	# ����.����� 1.2 �
	-1.9	30	0.6	0	# ����.����� 1 �
end
#	-0.32	360	34.2	1.272	# ������� 2 �, 16 ������
#	-0.28	394	38.3	1.357	# ������� 2 �, 24 ������
	-0.71	175	17.2	1.376	# ������� 1.5 �, 16 ������
	-0.66	196	20.6	1.500	# ������� 1.5 �, 24 ������
	-1.17	100	9.9	1.389	# ������� 1.2 �, 16 ������
	-1.01	114	12.5	1.542	# ������� 1.2 �, 24 ������
	-1.82	62	6.2	1.363	# ������� 1 �, 16 ������
	-1.55	74	8.3	1.539	# ������� 1 �, 24 ������
end
reset
