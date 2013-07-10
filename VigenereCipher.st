<?xml version="1.0"?>

<st-source>
<time-stamp>From VisualWorks® Personal Use Edition, 7.8 of 2011年3月30日 on 2012年3月4日 at 下午07時06分50秒</time-stamp>


<component-created>
<name>VigenereCipher</name> <type>package</type>
</component-created><!-- Package VigenereCipher* -->


<component-created>
<name>VigenereCipher</name> <type>package</type>
</component-created>

<class>
<name>VigenereCipher</name>
<environment>Smalltalk</environment>
<super>Core.Object</super>
<private>false</private>
<indexed-type>none</indexed-type>
<inst-vars>key key_length table </inst-vars>
<class-inst-vars></class-inst-vars>
<imports></imports>
<category></category>
<attributes>
<package>VigenereCipher</package>
</attributes>
</class>

<methods>
<class-id>VigenereCipher class</class-id> <category>instance creation</category>

<body package="VigenereCipher" selector="new">new	"Answer a newly created and initialized instance."	^super new initialize</body>
</methods>


<methods>
<class-id>VigenereCipher</class-id> <category>initialize-release</category>

<body package="VigenereCipher" selector="key:">key: aKey	key := aKey asUppercase.	key_length := key size.</body>

<body package="VigenereCipher" selector="decrypt:">decrypt: aStr	|str str_length output tmp1  j |		str := aStr asUppercase.	str_length := aStr size.		output := ByteArray new: str_length.	j := 1.		1 to: str_length do: [: i |				tmp1 := (str at: i ) asInteger.		((tmp1 &gt;= 65)&amp;(tmp1 &lt;= 91))		ifTrue:[						(j &gt; key_length ) ifTrue: [j := 1].			1 to: 26 do:[:k |				(((table at: (((key at:j) asInteger)- 64)) at: k) = (((str at: i) asInteger)-64))				ifTrue: [output at: i put: (k+64).				].			].		j := j+1.		]			ifFalse:[				output at: i put: (str at: i) asInteger.				"Transcript cr; show: 'output is OK'."].				].		^output.</body>

<body package="VigenereCipher" selector="initialize">initialize	"Initialize a newly created instance. This method must answer the receiver."	super initialize.	 self table_initlization.	" *** Replace this comment with the appropriate initialization code *** "	^self</body>

<body package="VigenereCipher" selector="table_initlization">table_initlization	" fill up the vigenere table "	| temp_array |		table := Array new: 26.	0 to: 25 do: [:i | 		temp_array := Array new: 26.		0 to: 25 do: [: j |		( i + j &lt; 26 )		ifTrue: [ temp_array at: (j+1) put: (i+j +1)]		ifFalse: [temp_array at: (j+1) put: ((i+j)\\26 +1) ] 		].	table at: (i+1) put: temp_array.	].</body>

<body package="VigenereCipher" selector="encrypt:">encrypt: aStr	|str str_length output tmp1 tmp2 j|		str := aStr asUppercase.	str_length := aStr size.		output := ByteArray new: str_length.	j := 1.	1 to: str_length do: [: i |		tmp1 := (str at: i ) asInteger.		((tmp1 &gt;= 65)&amp;(tmp1 &lt;= 91))		ifTrue:[			tmp1 := (tmp1 - 64).			(key_length &lt;j)			ifTrue: [			j:= 1.			].			 tmp2 := (key at: j) asInteger.			  tmp2 := (tmp2 - 64).			output at: i put: (((table at:tmp1) at: tmp2) + 64) .			j := j+1.				]		ifFalse:[				output at: i put: (str at: i) asInteger.				"Transcript cr; show: 'output is OK'."].				].		^output.</body>
</methods>



</st-source>
