// 6x6=36 pixels

//   0%    = 0 
//  16.66% = 6
//  33.33% = 12
//  50%    = 18
//  66.66% = 24
//  83.33% = 30
// 100%    = 36


_LabelBumpReconf
	; -7 => 0% [48*0]
	.byt 64+%000000
	.byt 64+%000000
	.byt 64+%000000
	.byt 64+%000000
	.byt 64+%000000
	.byt 64+%000000
	.byt 64+%000000
	.byt 64+%000000

	; -6 => 7.14% [3.4 pixels] 
	.byt 64+%100000
	.byt 64+%000000
	.byt 64+%000000
	.byt 64+%001000
	.byt 64+%000000
	.byt 64+%000010
	.byt 64+%000000
	.byt 64+%000000

	; -5 => 14.28% [6.8 pixels]
	.byt 64+%100000
	.byt 64+%000010
	.byt 64+%001000
	.byt 64+%000000
	.byt 64+%100000
	.byt 64+%001000
	.byt 64+%000010
	.byt 64+%000000

	; -4 => 21.42% [11.72 pixels]
	.byt 64+%100100
	.byt 64+%010010
	.byt 64+%001000
	.byt 64+%100010
	.byt 64+%001000
	.byt 64+%000101
	.byt 64+%010000
	.byt 64+%000010

	; -3 => 28.57% [13.71 pixels]
	.byt 64+%100100
	.byt 64+%010010
	.byt 64+%000100
	.byt 64+%001001
	.byt 64+%100100
	.byt 64+%010010
	.byt 64+%000100
	.byt 64+%001001

	; -2 => 35.71% [17.85 pixels]
	.byt 64+%100100
	.byt 64+%010010
	.byt 64+%001001
	.byt 64+%010010
	.byt 64+%100100
	.byt 64+%010010
	.byt 64+%001001
	.byt 64+%010010

	; -1 => 42.85% [20.56 pixels]
	.byt 64+%101010
	.byt 64+%010001
	.byt 64+%101010
	.byt 64+%000101
	.byt 64+%101010
	.byt 64+%010101
	.byt 64+%101000
	.byt 64+%010101

	; 0	=> 50% [24 points]
	.byt 64+%101010
	.byt 64+%010101
	.byt 64+%101010
	.byt 64+%010101
	.byt 64+%101010
	.byt 64+%010101
	.byt 64+%101010
	.byt 64+%010101

	; +1 => 57.14% [27.42 pixels]
	.byt 64+%101010
	.byt 64+%011101
	.byt 64+%101010
	.byt 64+%110101
	.byt 64+%101010
	.byt 64+%010101
	.byt 64+%101110
	.byt 64+%010101

	; +2 => 64.28% [30.85 pixels]
	.byt 64+%011011
	.byt 64+%101101
	.byt 64+%110110
	.byt 64+%101101
	.byt 64+%011011
	.byt 64+%101101
	.byt 64+%110110
	.byt 64+%101101

	; +3 => 71.42% [34.28 pixels]
	.byt 64+%011011
	.byt 64+%101101
	.byt 64+%111011
	.byt 64+%110110
	.byt 64+%011011
	.byt 64+%101101
	.byt 64+%111011
	.byt 64+%110110

	; +4 => 78.57% [37.71 pixels] 
	.byt 64+%011011
	.byt 64+%111111
	.byt 64+%101010
	.byt 64+%111111
	.byt 64+%011011
	.byt 64+%111111
	.byt 64+%101010
	.byt 64+%111111

	; +5 => 85.71% [41.14 pixels]
	.byt 64+%011111
	.byt 64+%111101
	.byt 64+%101111
	.byt 64+%111111
	.byt 64+%111011
	.byt 64+%101111
	.byt 64+%111101
	.byt 64+%110111

	; +6 => 92.85% [44.56 pixels]
	.byt 64+%011111
	.byt 64+%111111
	.byt 64+%111111
	.byt 64+%111011
	.byt 64+%111111
	.byt 64+%111111
	.byt 64+%110111
	.byt 64+%111111

	; +7 => 100% [48 pixels]
	.byt 64+%111111
	.byt 64+%111111
	.byt 64+%111111
	.byt 64+%111111
	.byt 64+%111111
	.byt 64+%111111
	.byt 64+%111111
	.byt 64+%111111

	; Bonus map...
	.byt 64+%111111
	.byt 64+%111111
	.byt 64+%111111
	.byt 64+%111111
	.byt 64+%111111
	.byt 64+%111111
	.byt 64+%111111
	.byt 64+%111111

	
	
	
	