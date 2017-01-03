function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Scope */
	this.urlHashMap["flightControl:256"] = "flightControl.h:119";
	/* <Root>/UDP Receive */
	this.urlHashMap["flightControl:54"] = "flightControl.c:151,163,978,998,1035,1046&flightControl.h:83,110,115";
	/* <Root>/runSensorFusion */
	this.urlHashMap["flightControl:59"] = "flightControl.c:165,877,1000,1026&flightControl.h:128,129";
	/* <S1>/Compare */
	this.urlHashMap["flightControl:63:2"] = "flightControl.c:168,876";
	/* <S1>/Constant */
	this.urlHashMap["flightControl:63:3"] = "flightControl.c:169&flightControl.h:153&flightControl_data.c:44";
	/* <S2>/Enable */
	this.urlHashMap["flightControl:61"] = "flightControl.c:166";
	/* <S2>/q */
	this.urlHashMap["flightControl:136"] = "flightControl.h:135&flightControl_data.c:26";
	/* <S2>/accel_w */
	this.urlHashMap["flightControl:228"] = "flightControl.c:1020,1025&flightControl.h:138&flightControl_data.c:29";
	/* <S2>/w_w */
	this.urlHashMap["flightControl:231"] = "flightControl.h:141&flightControl_data.c:32";
	/* <S2>/bortz_w */
	this.urlHashMap["flightControl:254"] = "flightControl.h:144&flightControl_data.c:35";
	/* <S3>/Constant2 */
	this.urlHashMap["flightControl:255:73"] = "flightControl.c:281&flightControl.h:150&flightControl_data.c:41";
	/* <S3>/Product */
	this.urlHashMap["flightControl:255:74"] = "flightControl.c:823,837&flightControl.h:85";
	/* <S3>/Product1 */
	this.urlHashMap["flightControl:255:75"] = "msg=rtwMsg_reducedBlock&block=flightControl:255:75";
	/* <S3>/Scope */
	this.urlHashMap["flightControl:255:76"] = "flightControl.h:123";
	/* <S3>/Selector */
	this.urlHashMap["flightControl:255:77"] = "flightControl.c:190&flightControl.h:95";
	/* <S3>/Selector1 */
	this.urlHashMap["flightControl:255:78"] = "flightControl.c:839&flightControl.h:96";
	/* <S3>/Selector2 */
	this.urlHashMap["flightControl:255:79"] = "flightControl.c:843&flightControl.h:97";
	/* <S3>/q2bortz */
	this.urlHashMap["flightControl:255:98"] = "msg=rtwMsg_CodeGenerationReducedBlock&block=flightControl:255:98";
	/* <S3>/q2cFcn */
	this.urlHashMap["flightControl:255:90"] = "flightControl.c:734&flightControl.h:90";
	/* <S3>/qinvFcn */
	this.urlHashMap["flightControl:255:91"] = "flightControl.c:735";
	/* <S3>/runMahonyUpdate */
	this.urlHashMap["flightControl:255:92"] = "flightControl.c:38,78,280,732,1010&flightControl.h:94,116,125";
	/* <S4>/Matrix
Concatenate */
	this.urlHashMap["flightControl:128"] = "flightControl.c:271&flightControl.h:92";
	/* <S4>/Matrix
Concatenate1 */
	this.urlHashMap["flightControl:129"] = "flightControl.c:176&flightControl.h:87";
	/* <S4>/Matrix
Concatenate2 */
	this.urlHashMap["flightControl:130"] = "flightControl.c:195&flightControl.h:88";
	/* <S4>/Reshape */
	this.urlHashMap["flightControl:125"] = "msg=rtwMsg_reducedBlock&block=flightControl:125";
	/* <S4>/Reshape1 */
	this.urlHashMap["flightControl:127"] = "msg=rtwMsg_reducedBlock&block=flightControl:127";
	/* <S5>/Constant */
	this.urlHashMap["flightControl:255:83"] = "flightControl.c:210&flightControl.h:147&flightControl_data.c:38";
	/* <S5>/Scope */
	this.urlHashMap["flightControl:255:84"] = "msg=rtwMsg_notTraceable&block=flightControl:255:84";
	/* <S5>/calibrate */
	this.urlHashMap["flightControl:255:86"] = "flightControl.c:209,269,1001&flightControl.h:89,126,127";
	/* <S6>:1 */
	this.urlHashMap["flightControl:255:98:1"] = "flightControl.c:858";
	/* <S6>:1:12 */
	this.urlHashMap["flightControl:255:98:1:12"] = "flightControl.c:859";
	/* <S6>:1:14 */
	this.urlHashMap["flightControl:255:98:1:14"] = "flightControl.c:861";
	/* <S6>:1:18 */
	this.urlHashMap["flightControl:255:98:1:18"] = "flightControl.c:863";
	/* <S6>:1:19 */
	this.urlHashMap["flightControl:255:98:1:19"] = "flightControl.c:864";
	/* <S6>:1:21 */
	this.urlHashMap["flightControl:255:98:1:21"] = "flightControl.c:866";
	/* <S6>:1:23 */
	this.urlHashMap["flightControl:255:98:1:23"] = "flightControl.c:868";
	/* <S7>:1 */
	this.urlHashMap["flightControl:255:90:1"] = "flightControl.c:757";
	/* <S7>:1:19 */
	this.urlHashMap["flightControl:255:90:1:19"] = "flightControl.c:758";
	/* <S7>:1:20 */
	this.urlHashMap["flightControl:255:90:1:20"] = "flightControl.c:760";
	/* <S7>:1:21 */
	this.urlHashMap["flightControl:255:90:1:21"] = "flightControl.c:761";
	/* <S7>:1:22 */
	this.urlHashMap["flightControl:255:90:1:22"] = "flightControl.c:762";
	/* <S7>:1:24 */
	this.urlHashMap["flightControl:255:90:1:24"] = "flightControl.c:764";
	/* <S7>:1:25 */
	this.urlHashMap["flightControl:255:90:1:25"] = "flightControl.c:767";
	/* <S7>:1:26 */
	this.urlHashMap["flightControl:255:90:1:26"] = "flightControl.c:770";
	/* <S7>:1:27 */
	this.urlHashMap["flightControl:255:90:1:27"] = "flightControl.c:773";
	/* <S7>:1:28 */
	this.urlHashMap["flightControl:255:90:1:28"] = "flightControl.c:776";
	/* <S7>:1:29 */
	this.urlHashMap["flightControl:255:90:1:29"] = "flightControl.c:779";
	/* <S7>:1:30 */
	this.urlHashMap["flightControl:255:90:1:30"] = "flightControl.c:782";
	/* <S7>:1:31 */
	this.urlHashMap["flightControl:255:90:1:31"] = "flightControl.c:785";
	/* <S7>:1:32 */
	this.urlHashMap["flightControl:255:90:1:32"] = "flightControl.c:788";
	/* <S7>:1:34 */
	this.urlHashMap["flightControl:255:90:1:34"] = "flightControl.c:792";
	/* <S7>:1:35 */
	this.urlHashMap["flightControl:255:90:1:35"] = "flightControl.c:793";
	/* <S7>:1:36 */
	this.urlHashMap["flightControl:255:90:1:36"] = "flightControl.c:794";
	/* <S7>:1:38 */
	this.urlHashMap["flightControl:255:90:1:38"] = "flightControl.c:795";
	/* <S7>:1:39 */
	this.urlHashMap["flightControl:255:90:1:39"] = "flightControl.c:798";
	/* <S7>:1:40 */
	this.urlHashMap["flightControl:255:90:1:40"] = "flightControl.c:801";
	/* <S7>:1:41 */
	this.urlHashMap["flightControl:255:90:1:41"] = "flightControl.c:804";
	/* <S7>:1:42 */
	this.urlHashMap["flightControl:255:90:1:42"] = "flightControl.c:807";
	/* <S7>:1:43 */
	this.urlHashMap["flightControl:255:90:1:43"] = "flightControl.c:810";
	/* <S7>:1:44 */
	this.urlHashMap["flightControl:255:90:1:44"] = "flightControl.c:813";
	/* <S7>:1:45 */
	this.urlHashMap["flightControl:255:90:1:45"] = "flightControl.c:816";
	/* <S7>:1:46 */
	this.urlHashMap["flightControl:255:90:1:46"] = "flightControl.c:819";
	/* <S8>:1 */
	this.urlHashMap["flightControl:255:91:1"] = "flightControl.c:738";
	/* <S8>:1:5 */
	this.urlHashMap["flightControl:255:91:1:5"] = "flightControl.c:739";
	/* <S8>:1:6 */
	this.urlHashMap["flightControl:255:91:1:6"] = "flightControl.c:740";
	/* <S9>:1 */
	this.urlHashMap["flightControl:255:92:1"] = "flightControl.c:283";
	/* <S9>:1:3 */
	this.urlHashMap["flightControl:255:92:1:3"] = "flightControl.c:284";
	/* <S9>:1:7 */
	this.urlHashMap["flightControl:255:92:1:7"] = "flightControl.c:285";
	/* <S9>:1:10 */
	this.urlHashMap["flightControl:255:92:1:10"] = "flightControl.c:286";
	/* <S9>:1:12 */
	this.urlHashMap["flightControl:255:92:1:12"] = "flightControl.c:289";
	/* <S9>:1:16 */
	this.urlHashMap["flightControl:255:92:1:16"] = "flightControl.c:290";
	/* <S9>:1:18 */
	this.urlHashMap["flightControl:255:92:1:18"] = "flightControl.c:353";
	/* <S9>:1:20 */
	this.urlHashMap["flightControl:255:92:1:20"] = "flightControl.c:355";
	/* <S9>:1:28 */
	this.urlHashMap["flightControl:255:92:1:28"] = "flightControl.c:363";
	/* <S9>:1:29 */
	this.urlHashMap["flightControl:255:92:1:29"] = "flightControl.c:364";
	/* <S9>:1:32 */
	this.urlHashMap["flightControl:255:92:1:32"] = "flightControl.c:366";
	/* <S9>:1:33 */
	this.urlHashMap["flightControl:255:92:1:33"] = "flightControl.c:387";
	/* <S9>:1:36 */
	this.urlHashMap["flightControl:255:92:1:36"] = "flightControl.c:401";
	/* <S9>:1:37 */
	this.urlHashMap["flightControl:255:92:1:37"] = "flightControl.c:421";
	/* <S9>:1:40 */
	this.urlHashMap["flightControl:255:92:1:40"] = "flightControl.c:432";
	/* <S9>:1:100 */
	this.urlHashMap["flightControl:255:92:1:100"] = "flightControl.c:444";
	/* <S9>:1:69 */
	this.urlHashMap["flightControl:255:92:1:69"] = "flightControl.c:450,482,642";
	/* <S9>:1:82 */
	this.urlHashMap["flightControl:255:92:1:82"] = "flightControl.c:462,494,654";
	/* <S9>:1:83 */
	this.urlHashMap["flightControl:255:92:1:83"] = "flightControl.c:467,495,655";
	/* <S9>:1:84 */
	this.urlHashMap["flightControl:255:92:1:84"] = "flightControl.c:472,496,656";
	/* <S9>:1:85 */
	this.urlHashMap["flightControl:255:92:1:85"] = "flightControl.c:477,497,657";
	/* <S9>:1:41 */
	this.urlHashMap["flightControl:255:92:1:41"] = "flightControl.c:498";
	/* <S9>:1:43 */
	this.urlHashMap["flightControl:255:92:1:43"] = "flightControl.c:536";
	/* <S9>:1:44 */
	this.urlHashMap["flightControl:255:92:1:44"] = "flightControl.c:537";
	/* <S9>:1:45 */
	this.urlHashMap["flightControl:255:92:1:45"] = "flightControl.c:538";
	/* <S9>:1:46 */
	this.urlHashMap["flightControl:255:92:1:46"] = "flightControl.c:539";
	/* <S9>:1:47 */
	this.urlHashMap["flightControl:255:92:1:47"] = "flightControl.c:540";
	/* <S9>:1:48 */
	this.urlHashMap["flightControl:255:92:1:48"] = "flightControl.c:541";
	/* <S9>:1:49 */
	this.urlHashMap["flightControl:255:92:1:49"] = "flightControl.c:542";
	/* <S9>:1:50 */
	this.urlHashMap["flightControl:255:92:1:50"] = "flightControl.c:543";
	/* <S9>:1:51 */
	this.urlHashMap["flightControl:255:92:1:51"] = "flightControl.c:544";
	/* <S9>:1:52 */
	this.urlHashMap["flightControl:255:92:1:52"] = "flightControl.c:545";
	/* <S9>:1:53 */
	this.urlHashMap["flightControl:255:92:1:53"] = "flightControl.c:546";
	/* <S9>:1:54 */
	this.urlHashMap["flightControl:255:92:1:54"] = "flightControl.c:547";
	/* <S9>:1:55 */
	this.urlHashMap["flightControl:255:92:1:55"] = "flightControl.c:548";
	/* <S9>:1:56 */
	this.urlHashMap["flightControl:255:92:1:56"] = "flightControl.c:629";
	/* <S9>:1:59 */
	this.urlHashMap["flightControl:255:92:1:59"] = "flightControl.c:637";
	/* <S9>:1:62 */
	this.urlHashMap["flightControl:255:92:1:62"] = "flightControl.c:659";
	/* <S9>:1:63 */
	this.urlHashMap["flightControl:255:92:1:63"] = "flightControl.c:702";
	/* <S9>:1:64 */
	this.urlHashMap["flightControl:255:92:1:64"] = "flightControl.c:708";
	/* <S9>:1:21 */
	this.urlHashMap["flightControl:255:92:1:21"] = "flightControl.c:723";
	/* <S9>:1:25 */
	this.urlHashMap["flightControl:255:92:1:25"] = "flightControl.c:726";
	/* <S9>:1:4 */
	this.urlHashMap["flightControl:255:92:1:4"] = "flightControl.c:1016";
	/* <S9>:1:5 */
	this.urlHashMap["flightControl:255:92:1:5"] = "flightControl.c:1017";
	/* <S10>:1 */
	this.urlHashMap["flightControl:255:86:1"] = "flightControl.c:212";
	/* <S10>:1:5 */
	this.urlHashMap["flightControl:255:86:1:5"] = "flightControl.c:213";
	/* <S10>:1:10 */
	this.urlHashMap["flightControl:255:86:1:10"] = "flightControl.c:214";
	/* <S10>:1:11 */
	this.urlHashMap["flightControl:255:86:1:11"] = "flightControl.c:216";
	/* <S10>:1:12 */
	this.urlHashMap["flightControl:255:86:1:12"] = "flightControl.c:242";
	/* <S10>:1:13 */
	this.urlHashMap["flightControl:255:86:1:13"] = "flightControl.c:243";
	/* <S10>:1:14 */
	this.urlHashMap["flightControl:255:86:1:14"] = "flightControl.c:248";
	/* <S10>:1:15 */
	this.urlHashMap["flightControl:255:86:1:15"] = "flightControl.c:250";
	/* <S10>:1:16 */
	this.urlHashMap["flightControl:255:86:1:16"] = "flightControl.c:259";
	/* <S10>:1:19 */
	this.urlHashMap["flightControl:255:86:1:19"] = "flightControl.c:272";
	/* <S10>:1:6 */
	this.urlHashMap["flightControl:255:86:1:6"] = "flightControl.c:1002";
	/* <S10>:1:7 */
	this.urlHashMap["flightControl:255:86:1:7"] = "flightControl.c:1005";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "flightControl"};
	this.sidHashMap["flightControl"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "flightControl:63"};
	this.sidHashMap["flightControl:63"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "flightControl:59"};
	this.sidHashMap["flightControl:59"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<S3>"] = {sid: "flightControl:255"};
	this.sidHashMap["flightControl:255"] = {rtwname: "<S3>"};
	this.rtwnameHashMap["<S4>"] = {sid: "flightControl:197"};
	this.sidHashMap["flightControl:197"] = {rtwname: "<S4>"};
	this.rtwnameHashMap["<S5>"] = {sid: "flightControl:255:80"};
	this.sidHashMap["flightControl:255:80"] = {rtwname: "<S5>"};
	this.rtwnameHashMap["<S6>"] = {sid: "flightControl:255:98"};
	this.sidHashMap["flightControl:255:98"] = {rtwname: "<S6>"};
	this.rtwnameHashMap["<S7>"] = {sid: "flightControl:255:90"};
	this.sidHashMap["flightControl:255:90"] = {rtwname: "<S7>"};
	this.rtwnameHashMap["<S8>"] = {sid: "flightControl:255:91"};
	this.sidHashMap["flightControl:255:91"] = {rtwname: "<S8>"};
	this.rtwnameHashMap["<S9>"] = {sid: "flightControl:255:92"};
	this.sidHashMap["flightControl:255:92"] = {rtwname: "<S9>"};
	this.rtwnameHashMap["<S10>"] = {sid: "flightControl:255:86"};
	this.sidHashMap["flightControl:255:86"] = {rtwname: "<S10>"};
	this.rtwnameHashMap["<Root>/Compare To Zero"] = {sid: "flightControl:63"};
	this.sidHashMap["flightControl:63"] = {rtwname: "<Root>/Compare To Zero"};
	this.rtwnameHashMap["<Root>/Scope"] = {sid: "flightControl:256"};
	this.sidHashMap["flightControl:256"] = {rtwname: "<Root>/Scope"};
	this.rtwnameHashMap["<Root>/UDP Receive"] = {sid: "flightControl:54"};
	this.sidHashMap["flightControl:54"] = {rtwname: "<Root>/UDP Receive"};
	this.rtwnameHashMap["<Root>/runSensorFusion"] = {sid: "flightControl:59"};
	this.sidHashMap["flightControl:59"] = {rtwname: "<Root>/runSensorFusion"};
	this.rtwnameHashMap["<S1>/u"] = {sid: "flightControl:63:1"};
	this.sidHashMap["flightControl:63:1"] = {rtwname: "<S1>/u"};
	this.rtwnameHashMap["<S1>/Compare"] = {sid: "flightControl:63:2"};
	this.sidHashMap["flightControl:63:2"] = {rtwname: "<S1>/Compare"};
	this.rtwnameHashMap["<S1>/Constant"] = {sid: "flightControl:63:3"};
	this.sidHashMap["flightControl:63:3"] = {rtwname: "<S1>/Constant"};
	this.rtwnameHashMap["<S1>/y"] = {sid: "flightControl:63:5"};
	this.sidHashMap["flightControl:63:5"] = {rtwname: "<S1>/y"};
	this.rtwnameHashMap["<S2>/udpData"] = {sid: "flightControl:60"};
	this.sidHashMap["flightControl:60"] = {rtwname: "<S2>/udpData"};
	this.rtwnameHashMap["<S2>/Enable"] = {sid: "flightControl:61"};
	this.sidHashMap["flightControl:61"] = {rtwname: "<S2>/Enable"};
	this.rtwnameHashMap["<S2>/translateIMUToWorld"] = {sid: "flightControl:255"};
	this.sidHashMap["flightControl:255"] = {rtwname: "<S2>/translateIMUToWorld"};
	this.rtwnameHashMap["<S2>/unpackData"] = {sid: "flightControl:197"};
	this.sidHashMap["flightControl:197"] = {rtwname: "<S2>/unpackData"};
	this.rtwnameHashMap["<S2>/q"] = {sid: "flightControl:136"};
	this.sidHashMap["flightControl:136"] = {rtwname: "<S2>/q"};
	this.rtwnameHashMap["<S2>/accel_w"] = {sid: "flightControl:228"};
	this.sidHashMap["flightControl:228"] = {rtwname: "<S2>/accel_w"};
	this.rtwnameHashMap["<S2>/w_w"] = {sid: "flightControl:231"};
	this.sidHashMap["flightControl:231"] = {rtwname: "<S2>/w_w"};
	this.rtwnameHashMap["<S2>/bortz_w"] = {sid: "flightControl:254"};
	this.sidHashMap["flightControl:254"] = {rtwname: "<S2>/bortz_w"};
	this.rtwnameHashMap["<S3>/accel_b"] = {sid: "flightControl:255:70"};
	this.sidHashMap["flightControl:255:70"] = {rtwname: "<S3>/accel_b"};
	this.rtwnameHashMap["<S3>/w_b"] = {sid: "flightControl:255:71"};
	this.sidHashMap["flightControl:255:71"] = {rtwname: "<S3>/w_b"};
	this.rtwnameHashMap["<S3>/mag_b"] = {sid: "flightControl:255:72"};
	this.sidHashMap["flightControl:255:72"] = {rtwname: "<S3>/mag_b"};
	this.rtwnameHashMap["<S3>/Constant2"] = {sid: "flightControl:255:73"};
	this.sidHashMap["flightControl:255:73"] = {rtwname: "<S3>/Constant2"};
	this.rtwnameHashMap["<S3>/Product"] = {sid: "flightControl:255:74"};
	this.sidHashMap["flightControl:255:74"] = {rtwname: "<S3>/Product"};
	this.rtwnameHashMap["<S3>/Product1"] = {sid: "flightControl:255:75"};
	this.sidHashMap["flightControl:255:75"] = {rtwname: "<S3>/Product1"};
	this.rtwnameHashMap["<S3>/Scope"] = {sid: "flightControl:255:76"};
	this.sidHashMap["flightControl:255:76"] = {rtwname: "<S3>/Scope"};
	this.rtwnameHashMap["<S3>/Selector"] = {sid: "flightControl:255:77"};
	this.sidHashMap["flightControl:255:77"] = {rtwname: "<S3>/Selector"};
	this.rtwnameHashMap["<S3>/Selector1"] = {sid: "flightControl:255:78"};
	this.sidHashMap["flightControl:255:78"] = {rtwname: "<S3>/Selector1"};
	this.rtwnameHashMap["<S3>/Selector2"] = {sid: "flightControl:255:79"};
	this.sidHashMap["flightControl:255:79"] = {rtwname: "<S3>/Selector2"};
	this.rtwnameHashMap["<S3>/calibrateSensorData"] = {sid: "flightControl:255:80"};
	this.sidHashMap["flightControl:255:80"] = {rtwname: "<S3>/calibrateSensorData"};
	this.rtwnameHashMap["<S3>/q2bortz"] = {sid: "flightControl:255:98"};
	this.sidHashMap["flightControl:255:98"] = {rtwname: "<S3>/q2bortz"};
	this.rtwnameHashMap["<S3>/q2cFcn"] = {sid: "flightControl:255:90"};
	this.sidHashMap["flightControl:255:90"] = {rtwname: "<S3>/q2cFcn"};
	this.rtwnameHashMap["<S3>/qinvFcn"] = {sid: "flightControl:255:91"};
	this.sidHashMap["flightControl:255:91"] = {rtwname: "<S3>/qinvFcn"};
	this.rtwnameHashMap["<S3>/runMahonyUpdate"] = {sid: "flightControl:255:92"};
	this.sidHashMap["flightControl:255:92"] = {rtwname: "<S3>/runMahonyUpdate"};
	this.rtwnameHashMap["<S3>/q"] = {sid: "flightControl:255:93"};
	this.sidHashMap["flightControl:255:93"] = {rtwname: "<S3>/q"};
	this.rtwnameHashMap["<S3>/accel_w"] = {sid: "flightControl:255:94"};
	this.sidHashMap["flightControl:255:94"] = {rtwname: "<S3>/accel_w"};
	this.rtwnameHashMap["<S3>/w_w"] = {sid: "flightControl:255:95"};
	this.sidHashMap["flightControl:255:95"] = {rtwname: "<S3>/w_w"};
	this.rtwnameHashMap["<S3>/bortz_w"] = {sid: "flightControl:255:96"};
	this.sidHashMap["flightControl:255:96"] = {rtwname: "<S3>/bortz_w"};
	this.rtwnameHashMap["<S4>/In1"] = {sid: "flightControl:198"};
	this.sidHashMap["flightControl:198"] = {rtwname: "<S4>/In1"};
	this.rtwnameHashMap["<S4>/Demux"] = {sid: "flightControl:124"};
	this.sidHashMap["flightControl:124"] = {rtwname: "<S4>/Demux"};
	this.rtwnameHashMap["<S4>/Demux1"] = {sid: "flightControl:126"};
	this.sidHashMap["flightControl:126"] = {rtwname: "<S4>/Demux1"};
	this.rtwnameHashMap["<S4>/Matrix Concatenate"] = {sid: "flightControl:128"};
	this.sidHashMap["flightControl:128"] = {rtwname: "<S4>/Matrix Concatenate"};
	this.rtwnameHashMap["<S4>/Matrix Concatenate1"] = {sid: "flightControl:129"};
	this.sidHashMap["flightControl:129"] = {rtwname: "<S4>/Matrix Concatenate1"};
	this.rtwnameHashMap["<S4>/Matrix Concatenate2"] = {sid: "flightControl:130"};
	this.sidHashMap["flightControl:130"] = {rtwname: "<S4>/Matrix Concatenate2"};
	this.rtwnameHashMap["<S4>/Reshape"] = {sid: "flightControl:125"};
	this.sidHashMap["flightControl:125"] = {rtwname: "<S4>/Reshape"};
	this.rtwnameHashMap["<S4>/Reshape1"] = {sid: "flightControl:127"};
	this.sidHashMap["flightControl:127"] = {rtwname: "<S4>/Reshape1"};
	this.rtwnameHashMap["<S4>/getAccelGyro"] = {sid: "flightControl:64"};
	this.sidHashMap["flightControl:64"] = {rtwname: "<S4>/getAccelGyro"};
	this.rtwnameHashMap["<S4>/getMag"] = {sid: "flightControl:66"};
	this.sidHashMap["flightControl:66"] = {rtwname: "<S4>/getMag"};
	this.rtwnameHashMap["<S4>/Accel"] = {sid: "flightControl:199"};
	this.sidHashMap["flightControl:199"] = {rtwname: "<S4>/Accel"};
	this.rtwnameHashMap["<S4>/Gyro"] = {sid: "flightControl:200"};
	this.sidHashMap["flightControl:200"] = {rtwname: "<S4>/Gyro"};
	this.rtwnameHashMap["<S4>/Mag"] = {sid: "flightControl:201"};
	this.sidHashMap["flightControl:201"] = {rtwname: "<S4>/Mag"};
	this.rtwnameHashMap["<S5>/accel"] = {sid: "flightControl:255:81"};
	this.sidHashMap["flightControl:255:81"] = {rtwname: "<S5>/accel"};
	this.rtwnameHashMap["<S5>/gyro"] = {sid: "flightControl:255:82"};
	this.sidHashMap["flightControl:255:82"] = {rtwname: "<S5>/gyro"};
	this.rtwnameHashMap["<S5>/Constant"] = {sid: "flightControl:255:83"};
	this.sidHashMap["flightControl:255:83"] = {rtwname: "<S5>/Constant"};
	this.rtwnameHashMap["<S5>/Scope"] = {sid: "flightControl:255:84"};
	this.sidHashMap["flightControl:255:84"] = {rtwname: "<S5>/Scope"};
	this.rtwnameHashMap["<S5>/Terminator1"] = {sid: "flightControl:255:85"};
	this.sidHashMap["flightControl:255:85"] = {rtwname: "<S5>/Terminator1"};
	this.rtwnameHashMap["<S5>/calibrate"] = {sid: "flightControl:255:86"};
	this.sidHashMap["flightControl:255:86"] = {rtwname: "<S5>/calibrate"};
	this.rtwnameHashMap["<S5>/accelCal"] = {sid: "flightControl:255:87"};
	this.sidHashMap["flightControl:255:87"] = {rtwname: "<S5>/accelCal"};
	this.rtwnameHashMap["<S5>/gyroCal"] = {sid: "flightControl:255:88"};
	this.sidHashMap["flightControl:255:88"] = {rtwname: "<S5>/gyroCal"};
	this.rtwnameHashMap["<S6>:1"] = {sid: "flightControl:255:98:1"};
	this.sidHashMap["flightControl:255:98:1"] = {rtwname: "<S6>:1"};
	this.rtwnameHashMap["<S6>:1:12"] = {sid: "flightControl:255:98:1:12"};
	this.sidHashMap["flightControl:255:98:1:12"] = {rtwname: "<S6>:1:12"};
	this.rtwnameHashMap["<S6>:1:14"] = {sid: "flightControl:255:98:1:14"};
	this.sidHashMap["flightControl:255:98:1:14"] = {rtwname: "<S6>:1:14"};
	this.rtwnameHashMap["<S6>:1:18"] = {sid: "flightControl:255:98:1:18"};
	this.sidHashMap["flightControl:255:98:1:18"] = {rtwname: "<S6>:1:18"};
	this.rtwnameHashMap["<S6>:1:19"] = {sid: "flightControl:255:98:1:19"};
	this.sidHashMap["flightControl:255:98:1:19"] = {rtwname: "<S6>:1:19"};
	this.rtwnameHashMap["<S6>:1:21"] = {sid: "flightControl:255:98:1:21"};
	this.sidHashMap["flightControl:255:98:1:21"] = {rtwname: "<S6>:1:21"};
	this.rtwnameHashMap["<S6>:1:23"] = {sid: "flightControl:255:98:1:23"};
	this.sidHashMap["flightControl:255:98:1:23"] = {rtwname: "<S6>:1:23"};
	this.rtwnameHashMap["<S7>:1"] = {sid: "flightControl:255:90:1"};
	this.sidHashMap["flightControl:255:90:1"] = {rtwname: "<S7>:1"};
	this.rtwnameHashMap["<S7>:1:19"] = {sid: "flightControl:255:90:1:19"};
	this.sidHashMap["flightControl:255:90:1:19"] = {rtwname: "<S7>:1:19"};
	this.rtwnameHashMap["<S7>:1:20"] = {sid: "flightControl:255:90:1:20"};
	this.sidHashMap["flightControl:255:90:1:20"] = {rtwname: "<S7>:1:20"};
	this.rtwnameHashMap["<S7>:1:21"] = {sid: "flightControl:255:90:1:21"};
	this.sidHashMap["flightControl:255:90:1:21"] = {rtwname: "<S7>:1:21"};
	this.rtwnameHashMap["<S7>:1:22"] = {sid: "flightControl:255:90:1:22"};
	this.sidHashMap["flightControl:255:90:1:22"] = {rtwname: "<S7>:1:22"};
	this.rtwnameHashMap["<S7>:1:24"] = {sid: "flightControl:255:90:1:24"};
	this.sidHashMap["flightControl:255:90:1:24"] = {rtwname: "<S7>:1:24"};
	this.rtwnameHashMap["<S7>:1:25"] = {sid: "flightControl:255:90:1:25"};
	this.sidHashMap["flightControl:255:90:1:25"] = {rtwname: "<S7>:1:25"};
	this.rtwnameHashMap["<S7>:1:26"] = {sid: "flightControl:255:90:1:26"};
	this.sidHashMap["flightControl:255:90:1:26"] = {rtwname: "<S7>:1:26"};
	this.rtwnameHashMap["<S7>:1:27"] = {sid: "flightControl:255:90:1:27"};
	this.sidHashMap["flightControl:255:90:1:27"] = {rtwname: "<S7>:1:27"};
	this.rtwnameHashMap["<S7>:1:28"] = {sid: "flightControl:255:90:1:28"};
	this.sidHashMap["flightControl:255:90:1:28"] = {rtwname: "<S7>:1:28"};
	this.rtwnameHashMap["<S7>:1:29"] = {sid: "flightControl:255:90:1:29"};
	this.sidHashMap["flightControl:255:90:1:29"] = {rtwname: "<S7>:1:29"};
	this.rtwnameHashMap["<S7>:1:30"] = {sid: "flightControl:255:90:1:30"};
	this.sidHashMap["flightControl:255:90:1:30"] = {rtwname: "<S7>:1:30"};
	this.rtwnameHashMap["<S7>:1:31"] = {sid: "flightControl:255:90:1:31"};
	this.sidHashMap["flightControl:255:90:1:31"] = {rtwname: "<S7>:1:31"};
	this.rtwnameHashMap["<S7>:1:32"] = {sid: "flightControl:255:90:1:32"};
	this.sidHashMap["flightControl:255:90:1:32"] = {rtwname: "<S7>:1:32"};
	this.rtwnameHashMap["<S7>:1:34"] = {sid: "flightControl:255:90:1:34"};
	this.sidHashMap["flightControl:255:90:1:34"] = {rtwname: "<S7>:1:34"};
	this.rtwnameHashMap["<S7>:1:35"] = {sid: "flightControl:255:90:1:35"};
	this.sidHashMap["flightControl:255:90:1:35"] = {rtwname: "<S7>:1:35"};
	this.rtwnameHashMap["<S7>:1:36"] = {sid: "flightControl:255:90:1:36"};
	this.sidHashMap["flightControl:255:90:1:36"] = {rtwname: "<S7>:1:36"};
	this.rtwnameHashMap["<S7>:1:38"] = {sid: "flightControl:255:90:1:38"};
	this.sidHashMap["flightControl:255:90:1:38"] = {rtwname: "<S7>:1:38"};
	this.rtwnameHashMap["<S7>:1:39"] = {sid: "flightControl:255:90:1:39"};
	this.sidHashMap["flightControl:255:90:1:39"] = {rtwname: "<S7>:1:39"};
	this.rtwnameHashMap["<S7>:1:40"] = {sid: "flightControl:255:90:1:40"};
	this.sidHashMap["flightControl:255:90:1:40"] = {rtwname: "<S7>:1:40"};
	this.rtwnameHashMap["<S7>:1:41"] = {sid: "flightControl:255:90:1:41"};
	this.sidHashMap["flightControl:255:90:1:41"] = {rtwname: "<S7>:1:41"};
	this.rtwnameHashMap["<S7>:1:42"] = {sid: "flightControl:255:90:1:42"};
	this.sidHashMap["flightControl:255:90:1:42"] = {rtwname: "<S7>:1:42"};
	this.rtwnameHashMap["<S7>:1:43"] = {sid: "flightControl:255:90:1:43"};
	this.sidHashMap["flightControl:255:90:1:43"] = {rtwname: "<S7>:1:43"};
	this.rtwnameHashMap["<S7>:1:44"] = {sid: "flightControl:255:90:1:44"};
	this.sidHashMap["flightControl:255:90:1:44"] = {rtwname: "<S7>:1:44"};
	this.rtwnameHashMap["<S7>:1:45"] = {sid: "flightControl:255:90:1:45"};
	this.sidHashMap["flightControl:255:90:1:45"] = {rtwname: "<S7>:1:45"};
	this.rtwnameHashMap["<S7>:1:46"] = {sid: "flightControl:255:90:1:46"};
	this.sidHashMap["flightControl:255:90:1:46"] = {rtwname: "<S7>:1:46"};
	this.rtwnameHashMap["<S8>:1"] = {sid: "flightControl:255:91:1"};
	this.sidHashMap["flightControl:255:91:1"] = {rtwname: "<S8>:1"};
	this.rtwnameHashMap["<S8>:1:5"] = {sid: "flightControl:255:91:1:5"};
	this.sidHashMap["flightControl:255:91:1:5"] = {rtwname: "<S8>:1:5"};
	this.rtwnameHashMap["<S8>:1:6"] = {sid: "flightControl:255:91:1:6"};
	this.sidHashMap["flightControl:255:91:1:6"] = {rtwname: "<S8>:1:6"};
	this.rtwnameHashMap["<S9>:1"] = {sid: "flightControl:255:92:1"};
	this.sidHashMap["flightControl:255:92:1"] = {rtwname: "<S9>:1"};
	this.rtwnameHashMap["<S9>:1:3"] = {sid: "flightControl:255:92:1:3"};
	this.sidHashMap["flightControl:255:92:1:3"] = {rtwname: "<S9>:1:3"};
	this.rtwnameHashMap["<S9>:1:7"] = {sid: "flightControl:255:92:1:7"};
	this.sidHashMap["flightControl:255:92:1:7"] = {rtwname: "<S9>:1:7"};
	this.rtwnameHashMap["<S9>:1:10"] = {sid: "flightControl:255:92:1:10"};
	this.sidHashMap["flightControl:255:92:1:10"] = {rtwname: "<S9>:1:10"};
	this.rtwnameHashMap["<S9>:1:12"] = {sid: "flightControl:255:92:1:12"};
	this.sidHashMap["flightControl:255:92:1:12"] = {rtwname: "<S9>:1:12"};
	this.rtwnameHashMap["<S9>:1:16"] = {sid: "flightControl:255:92:1:16"};
	this.sidHashMap["flightControl:255:92:1:16"] = {rtwname: "<S9>:1:16"};
	this.rtwnameHashMap["<S9>:1:18"] = {sid: "flightControl:255:92:1:18"};
	this.sidHashMap["flightControl:255:92:1:18"] = {rtwname: "<S9>:1:18"};
	this.rtwnameHashMap["<S9>:1:20"] = {sid: "flightControl:255:92:1:20"};
	this.sidHashMap["flightControl:255:92:1:20"] = {rtwname: "<S9>:1:20"};
	this.rtwnameHashMap["<S9>:1:28"] = {sid: "flightControl:255:92:1:28"};
	this.sidHashMap["flightControl:255:92:1:28"] = {rtwname: "<S9>:1:28"};
	this.rtwnameHashMap["<S9>:1:29"] = {sid: "flightControl:255:92:1:29"};
	this.sidHashMap["flightControl:255:92:1:29"] = {rtwname: "<S9>:1:29"};
	this.rtwnameHashMap["<S9>:1:32"] = {sid: "flightControl:255:92:1:32"};
	this.sidHashMap["flightControl:255:92:1:32"] = {rtwname: "<S9>:1:32"};
	this.rtwnameHashMap["<S9>:1:33"] = {sid: "flightControl:255:92:1:33"};
	this.sidHashMap["flightControl:255:92:1:33"] = {rtwname: "<S9>:1:33"};
	this.rtwnameHashMap["<S9>:1:36"] = {sid: "flightControl:255:92:1:36"};
	this.sidHashMap["flightControl:255:92:1:36"] = {rtwname: "<S9>:1:36"};
	this.rtwnameHashMap["<S9>:1:37"] = {sid: "flightControl:255:92:1:37"};
	this.sidHashMap["flightControl:255:92:1:37"] = {rtwname: "<S9>:1:37"};
	this.rtwnameHashMap["<S9>:1:40"] = {sid: "flightControl:255:92:1:40"};
	this.sidHashMap["flightControl:255:92:1:40"] = {rtwname: "<S9>:1:40"};
	this.rtwnameHashMap["<S9>:1:100"] = {sid: "flightControl:255:92:1:100"};
	this.sidHashMap["flightControl:255:92:1:100"] = {rtwname: "<S9>:1:100"};
	this.rtwnameHashMap["<S9>:1:69"] = {sid: "flightControl:255:92:1:69"};
	this.sidHashMap["flightControl:255:92:1:69"] = {rtwname: "<S9>:1:69"};
	this.rtwnameHashMap["<S9>:1:82"] = {sid: "flightControl:255:92:1:82"};
	this.sidHashMap["flightControl:255:92:1:82"] = {rtwname: "<S9>:1:82"};
	this.rtwnameHashMap["<S9>:1:83"] = {sid: "flightControl:255:92:1:83"};
	this.sidHashMap["flightControl:255:92:1:83"] = {rtwname: "<S9>:1:83"};
	this.rtwnameHashMap["<S9>:1:84"] = {sid: "flightControl:255:92:1:84"};
	this.sidHashMap["flightControl:255:92:1:84"] = {rtwname: "<S9>:1:84"};
	this.rtwnameHashMap["<S9>:1:85"] = {sid: "flightControl:255:92:1:85"};
	this.sidHashMap["flightControl:255:92:1:85"] = {rtwname: "<S9>:1:85"};
	this.rtwnameHashMap["<S9>:1:41"] = {sid: "flightControl:255:92:1:41"};
	this.sidHashMap["flightControl:255:92:1:41"] = {rtwname: "<S9>:1:41"};
	this.rtwnameHashMap["<S9>:1:43"] = {sid: "flightControl:255:92:1:43"};
	this.sidHashMap["flightControl:255:92:1:43"] = {rtwname: "<S9>:1:43"};
	this.rtwnameHashMap["<S9>:1:44"] = {sid: "flightControl:255:92:1:44"};
	this.sidHashMap["flightControl:255:92:1:44"] = {rtwname: "<S9>:1:44"};
	this.rtwnameHashMap["<S9>:1:45"] = {sid: "flightControl:255:92:1:45"};
	this.sidHashMap["flightControl:255:92:1:45"] = {rtwname: "<S9>:1:45"};
	this.rtwnameHashMap["<S9>:1:46"] = {sid: "flightControl:255:92:1:46"};
	this.sidHashMap["flightControl:255:92:1:46"] = {rtwname: "<S9>:1:46"};
	this.rtwnameHashMap["<S9>:1:47"] = {sid: "flightControl:255:92:1:47"};
	this.sidHashMap["flightControl:255:92:1:47"] = {rtwname: "<S9>:1:47"};
	this.rtwnameHashMap["<S9>:1:48"] = {sid: "flightControl:255:92:1:48"};
	this.sidHashMap["flightControl:255:92:1:48"] = {rtwname: "<S9>:1:48"};
	this.rtwnameHashMap["<S9>:1:49"] = {sid: "flightControl:255:92:1:49"};
	this.sidHashMap["flightControl:255:92:1:49"] = {rtwname: "<S9>:1:49"};
	this.rtwnameHashMap["<S9>:1:50"] = {sid: "flightControl:255:92:1:50"};
	this.sidHashMap["flightControl:255:92:1:50"] = {rtwname: "<S9>:1:50"};
	this.rtwnameHashMap["<S9>:1:51"] = {sid: "flightControl:255:92:1:51"};
	this.sidHashMap["flightControl:255:92:1:51"] = {rtwname: "<S9>:1:51"};
	this.rtwnameHashMap["<S9>:1:52"] = {sid: "flightControl:255:92:1:52"};
	this.sidHashMap["flightControl:255:92:1:52"] = {rtwname: "<S9>:1:52"};
	this.rtwnameHashMap["<S9>:1:53"] = {sid: "flightControl:255:92:1:53"};
	this.sidHashMap["flightControl:255:92:1:53"] = {rtwname: "<S9>:1:53"};
	this.rtwnameHashMap["<S9>:1:54"] = {sid: "flightControl:255:92:1:54"};
	this.sidHashMap["flightControl:255:92:1:54"] = {rtwname: "<S9>:1:54"};
	this.rtwnameHashMap["<S9>:1:55"] = {sid: "flightControl:255:92:1:55"};
	this.sidHashMap["flightControl:255:92:1:55"] = {rtwname: "<S9>:1:55"};
	this.rtwnameHashMap["<S9>:1:56"] = {sid: "flightControl:255:92:1:56"};
	this.sidHashMap["flightControl:255:92:1:56"] = {rtwname: "<S9>:1:56"};
	this.rtwnameHashMap["<S9>:1:59"] = {sid: "flightControl:255:92:1:59"};
	this.sidHashMap["flightControl:255:92:1:59"] = {rtwname: "<S9>:1:59"};
	this.rtwnameHashMap["<S9>:1:62"] = {sid: "flightControl:255:92:1:62"};
	this.sidHashMap["flightControl:255:92:1:62"] = {rtwname: "<S9>:1:62"};
	this.rtwnameHashMap["<S9>:1:63"] = {sid: "flightControl:255:92:1:63"};
	this.sidHashMap["flightControl:255:92:1:63"] = {rtwname: "<S9>:1:63"};
	this.rtwnameHashMap["<S9>:1:64"] = {sid: "flightControl:255:92:1:64"};
	this.sidHashMap["flightControl:255:92:1:64"] = {rtwname: "<S9>:1:64"};
	this.rtwnameHashMap["<S9>:1:21"] = {sid: "flightControl:255:92:1:21"};
	this.sidHashMap["flightControl:255:92:1:21"] = {rtwname: "<S9>:1:21"};
	this.rtwnameHashMap["<S9>:1:25"] = {sid: "flightControl:255:92:1:25"};
	this.sidHashMap["flightControl:255:92:1:25"] = {rtwname: "<S9>:1:25"};
	this.rtwnameHashMap["<S9>:1:4"] = {sid: "flightControl:255:92:1:4"};
	this.sidHashMap["flightControl:255:92:1:4"] = {rtwname: "<S9>:1:4"};
	this.rtwnameHashMap["<S9>:1:5"] = {sid: "flightControl:255:92:1:5"};
	this.sidHashMap["flightControl:255:92:1:5"] = {rtwname: "<S9>:1:5"};
	this.rtwnameHashMap["<S10>:1"] = {sid: "flightControl:255:86:1"};
	this.sidHashMap["flightControl:255:86:1"] = {rtwname: "<S10>:1"};
	this.rtwnameHashMap["<S10>:1:5"] = {sid: "flightControl:255:86:1:5"};
	this.sidHashMap["flightControl:255:86:1:5"] = {rtwname: "<S10>:1:5"};
	this.rtwnameHashMap["<S10>:1:10"] = {sid: "flightControl:255:86:1:10"};
	this.sidHashMap["flightControl:255:86:1:10"] = {rtwname: "<S10>:1:10"};
	this.rtwnameHashMap["<S10>:1:11"] = {sid: "flightControl:255:86:1:11"};
	this.sidHashMap["flightControl:255:86:1:11"] = {rtwname: "<S10>:1:11"};
	this.rtwnameHashMap["<S10>:1:12"] = {sid: "flightControl:255:86:1:12"};
	this.sidHashMap["flightControl:255:86:1:12"] = {rtwname: "<S10>:1:12"};
	this.rtwnameHashMap["<S10>:1:13"] = {sid: "flightControl:255:86:1:13"};
	this.sidHashMap["flightControl:255:86:1:13"] = {rtwname: "<S10>:1:13"};
	this.rtwnameHashMap["<S10>:1:14"] = {sid: "flightControl:255:86:1:14"};
	this.sidHashMap["flightControl:255:86:1:14"] = {rtwname: "<S10>:1:14"};
	this.rtwnameHashMap["<S10>:1:15"] = {sid: "flightControl:255:86:1:15"};
	this.sidHashMap["flightControl:255:86:1:15"] = {rtwname: "<S10>:1:15"};
	this.rtwnameHashMap["<S10>:1:16"] = {sid: "flightControl:255:86:1:16"};
	this.sidHashMap["flightControl:255:86:1:16"] = {rtwname: "<S10>:1:16"};
	this.rtwnameHashMap["<S10>:1:19"] = {sid: "flightControl:255:86:1:19"};
	this.sidHashMap["flightControl:255:86:1:19"] = {rtwname: "<S10>:1:19"};
	this.rtwnameHashMap["<S10>:1:6"] = {sid: "flightControl:255:86:1:6"};
	this.sidHashMap["flightControl:255:86:1:6"] = {rtwname: "<S10>:1:6"};
	this.rtwnameHashMap["<S10>:1:7"] = {sid: "flightControl:255:86:1:7"};
	this.sidHashMap["flightControl:255:86:1:7"] = {rtwname: "<S10>:1:7"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
