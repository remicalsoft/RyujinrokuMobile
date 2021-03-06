#pragma once


enum eFaceType {
	eDefault,
	eIkari,
	eKomatta,
	eMu,
	eOdoroki,
	eNiconico,
	eKiri,
	eKyoton,
	eAkire,
	eEhhen,
	eShobon,
	eDoya,
	eKeikai,
	eAseri,
	eAseriEye,
	eDefEye,

	eFaceNum,
};

enum eChara {
	eAisha,
	eYohi,
	eToko,
	eYuyumi,
	eDakki,
	eRyuki,
	eRyubi,
	eEnd,
};

static const char *charaName[] = {
	"アイシャ",
	"妖飛(ようひ)",
	"濤子(とうこ)",
	"幽々巳(ゆゆみ)",
	"妲己(だっき)",
	"龍姫(りゅうき)",
	"龍美(りゅうび)",
};

static const char *charaFolderName[] = {
	"00.aisha",
	"01.yohi",
	"02.toko",
	"03.yuyumi",
	"04.dakki",
	"05.ryuki",
	"06.ryubi",
};

static const char *faceFileName[] = {
	"00.default",
	"01.ikari",
	"02.komatta",
	"03.mu",
	"04.odoroki",
	"05.niconico",
	"06.kiri",
	"07.kyoton",
	"08.akire",
	"09.ehhen",
	"10.shobon",
	"11.doya",
	"12.keikai",
	"13.aseri",
	"14.aseriCloseEye",
	"15.defaultCloseEye"
};

typedef struct {
	eChara    chara;
	eFaceType faceType;
	char *serif;
}Talk_t;

static const Talk_t talk[][64] = {
	{
		{ eYohi,  eDefault,	"フンフン〜♪" },
		{ eAisha, eMu,		"こんな薄暗い中、何してるの？" },
		{ eYohi,  eNiconico,"夜だと妖精達がとても元気なの。だから私もご機嫌なのよ" },
		{ eAisha, eAkire,	"人間はこんな暗いままじゃ元気でないよ" },
		{ eYohi,  eAkire,	"人間って陰気ねぇ" },
		{ eAisha, eAkire,	"暗いところが好きな妖人に言われたくないな…" },
		{ eYohi,  eDefault, "人間がこんな所に来るなんて珍しいじゃない" },
		{ eYohi,  eNiconico, "あなたも夜に浮かれて妖精達と踊りに来たの？" },
		{ eAisha, eIkari,	"違うよ、ボクは夜が明けなくて困ってるんだ" },
		{ eYohi,  eDefault, "あら、夜って素敵じゃない？これからもずっと続くのよ、素晴らしいわ" },
		{ eAisha, eOdoroki, "これからもずっと続くの？" },
		{ eYohi,  eNiconico, "そうよ、素敵でしょ？" },
		{ eAisha, eIkari,	"迷惑だよ！" },
		{ eAisha, eMu,		"キミはここ１ヶ月朝が来てない理由を何か知っているの？" },
		{ eYohi,  eDefault, "もちろん知ってるわ" },
		{ eAisha, eKyoton,	"ホント？！教えてよ！" },
		{ eYohi,  eKomatta, "いやよ。この子達は夜が好きなの、貴方に好き勝手されては困るわ" },
		{ eAisha, eKomatta, "そんな…" },
		{ eYohi,  eAkire,   "…でもそうね、どうしても知りたいなら私と勝負よ" },
		{ eYohi,  eAkire,   "もし貴方が勝ったら教えてあげてもいいわ" },
		{ eAisha, eNiconico,"ありがとう！" },
		{ eYohi,  eDefault, "あら、もう勝ったつもり？私が勝てば夜はそのままよ。いい？" },
		{ eAisha, eKiri,	"望むところさ！" },
		{ eAisha, eDefault, nullptr },
		{ eAisha, eKiri,	"ボクの勝ちだね。さぁ知ってることを話してもらうよ" },
		{ eYohi,  eKomatta, "あのお方が長い夜をお作りになっているのよ" },
		{ eAisha, eMu,		"あのお方？" },
		{ eYohi,  eAkire,   "知りたきゃ自分で調べるのね" },
		{ eAisha, eKomatta, "えぇ、せっかく勝負に勝ったのに情報それだけ…" },
		{ eEnd, eDefault, nullptr },
	},
	{
		{ eToko, eDoya,    "そこの人間、どいたどいた！" },
		{ eAisha,eOdoroki, "わわ。なになに？！" },
		{ eToko, eDefault, "そこから花火を打ち上げるんだよ！真っ黒焦げになりたいのかい？" },
		{ eAisha,eMu,      "この辺は妖人たちが祭りをやっているんだね" },
		{ eToko, eEhhen,   "そーさ、今日で9才になられた龍姫お嬢様の誕生日だからね！" },
		{ eToko, eDoya,    "これから世界は妖人の天下になるよ！" },
		{ eAisha,eDefault, "忙しいとこ悪いんだけど『長い夜を作ったあの方』って誰なのか知ってる？" },
		{ eToko, eKeikai,  "…龍姫お嬢様に何か用かぃ" },
		{ eAisha,eMu,      "その龍姫お嬢様が長い夜を作ったの？ボク達は朝が来なくて困ってるんだよ" },
		{ eToko, eShobon,  "あたしは朝が来たら困るんだ" },
		{ eToko, eNiconico,"いいじゃないか、花火があれば太陽なんていらないだろ？" },
		{ eAisha,eAkire,   "キミたち妖人は本当人のことを考えてないんだから…" },
		{ eToko, eAkire,   "ったく、人間にもキレーな花火を見せてやろうって言ってやってんのに…" },
		{ eToko, eAkire,   "お前らこそ妖人の心遣いをわかってないぜ！" },
		{ eToko, eDoya,    "煌めく火薬は闘志を燃やし、轟く波動は気魂を揺らす" },
		{ eToko, eDoya,    "あたしの花火、特等席で貪りな！" },
		{ eAisha,eDefault, nullptr },
		{ eToko, eShobon,  "あぁ…あたしの花火…" },
		{ eAisha,eNiconico,"花火師としての腕は一人前みたいだけど、" },
		{ eAisha,eNiconico,"妖人としてはまだまだ半人前みたいだね" },
		{ eAisha,eDefault, "さぁ、通してもらうよ" },
		{ eEnd,eDefault, nullptr },
	},
	{
		{ eAisha, eKomatta,	"はぁ…結構奥まで来ちゃったけど" },
		{ eAisha, eKomatta,	"龍姫お嬢様とかいう人のいる場所はこっちで合ってるのかな…" },
		{ eYuyumi,eDefault,	"いっちに、さーんし！" },
		{ eAisha, eOdoroki,	"わっ出た！！お化け！" },
		{ eYuyumi,eDefault,	"おんやぁー？こんなところに人間なんて珍しいのぅ" },
		{ eYuyumi,eNiconico,"お主も一緒に体操するかの？" },
		{ eAisha, eAkire,	"…体操は日差しを浴びながら爽やかにしたいよ" },
		{ eYuyumi,eDefault,	"だがお主、憑かれた顔しとるのぅ。平気かの？" },
		{ eAisha, eMu,		"そりゃー毎日魔法を使ってヘトヘトな上、" },
		{ eAisha, eMu,		"キミの仲間がたくさん邪魔してきたからね…そりゃ疲れるよ" },
		{ eYuyumi,eDefault,	"ほぅ、それはそれは" },
		{ eAisha, eKyoton,	"ところでキミは龍姫お嬢様と言う人を知ってる？" },
		{ eYuyumi,eMu,		"もちろんだとも。しかしお主は龍姫お嬢様に会うことは叶わんよ" },
		{ eAisha, eKyoton,	"何故？" },
		{ eYuyumi,eMu,		"我らが龍姫お嬢様には妲己様というそれはお強い側近がいらっしゃるでな" },
		{ eYuyumi,eDoya,	"怪我したくなければ立ち去るが良い" },
		{ eAisha, eIkari,	"妲己様…？側近だかなんだか知らないけど、ボクがやっつけてやる！" },
		{ eYuyumi,eMu,		"わざわざ注意してやったのに…" },
		{ eYuyumi,eAkire,	"妲己様のお力も知らぬとは世間知らずの子供じゃの" },
		{ eYuyumi,eIkari,	"しかし龍姫お嬢様の邪魔をすることは我が許さん" },
		{ eYuyumi,eIkari,	"ここで、お主の持ってるなけなしの光を全て頂くよ！" },
		{ eAisha, eDefault, nullptr },
		{ eAisha, eMu,      "いい加減成仏しなよ…" },
		{ eYuyumi,eShobon,  "うぅ…龍姫お嬢様ぁ…" },
		{ eEnd, eDefault, nullptr },
	},
	{
		{ eAisha,eDefault,	"…やっとここまで着いた。キミが妲己だね" },
		{ eDakki,eDefault,	"何だ、迷子か？森の外まで帰してやろうか" },
		{ eAisha,eIkari,	"ボクは子供じゃない！！" },
		{ eDakki,eDefault,	"子供も愚民も下僕も皆同じさ。中身は虚ろ" },
		{ eAisha,eMu,		"龍姫って人に会わせてよ！" },
		{ eDakki,eDefault,	"人間風情が高貴な龍姫お嬢様にお会いできるわけなかろう" },
		{ eAisha,eDefault,	"でもその人に会ってなんとかしてもらわないと" },
		{ eAisha,eIkari,	"ボクたちの村に朝が戻ってこないんだ！" },
		{ eDakki,eDefault,	"光は龍姫お嬢様にとって必要な栄養源" },
		{ eDakki,eDefEye,	"成長期ゆえ、これから更に食欲も増えよう" },
		{ eDakki,eDefault,	"私たちも今まで以上に光集めにいそしまねばな" },
		{ eAisha,eIkari,	"やめてよ！" },
		{ eDakki,eDefEye,	"あきらめよ、朝は来ぬ" },
		{ eAisha,eIkari,	"なら…ボクが止めさせる！" },
		{ eDakki,eDefault,	"くっくっ…面白いことを言う。人間如きが妖人に何ができる" },
		{ eAisha,eNiconico,	"それはやってみなきゃ分かんないよ！" },
		{ eDakki,eDefault,	"ん…？" },
		{ eDakki,eNiconico,	"なるほど…ここまで来られただけあって、やたらと光の匂いのする子供だな" },
		{ eAisha,eKiri,		"ボクを甘く見ると痛い目に合うよ" },
		{ eDakki,eNiconico,	"フッ。龍姫お嬢様をお守りする側近としてここを通すわけにはいかん" },
		{ eDakki,eDefault,	"貴様からも存分に光をいただくとしよう" },
		{ eAisha,eDefault,	nullptr },
		{ eDakki,eAseri,	"クッ…、私がこんな人間如きに…" },
		{ eAisha,eNiconico,	"さっ、龍姫ちゃんの所へ行かせてもらうよ" },
		{ eDakki,eAseriEye,	"龍姫お嬢様…申し訳ございません…" },
		{ eEnd,eDefault,	nullptr },
	},
	{ 
		{ eRyuki, eMu,      "…おなかへったなぁ、みんなまだ光を集めてるのかなぁ…" },
		{ eAisha, eDefault, "…キミが龍姫ちゃん？" },
		{ eRyuki, eKyoton,  "そうだけど、あなた、だぁれ？" },
		{ eAisha, eDefault, "ボクはアイシャ。村の魔術師だよ。村に朝を取り戻しに来たんだ" },
		{ eRyuki, eMu,      "ふうん。それより妲己は〜？" },
		{ eAisha, eKiri,    "残念だったね、光を集めている手下たちはみんなボクがやっつけたよ" },
		{ eRyuki, eAkire,   "えーアタシのご飯はー？" },
		{ eAisha, eIkari,   "キミが好き放題光を食べるせいで人間はみんな迷惑してるんだよ" },
		{ eRyuki, eMu,      "だってお腹減るんだもんー" },
		{ eRyuki, eKyoton,  "あや？…あなたからおいしそうな光のにおいがプンプンする♪" },
		{ eRyuki, eNiconico,"アタシお腹減って我慢できない。ちょっと味見させて？" },
		{ eAisha, eKiri,    "いいよ、味わわせてあげる" },
		{ eAisha, eIkari,   "キミの手下を倒してきた、このボクの魔術をね！" },
		{ eAisha, eDefault, nullptr },
		{ eRyuki, eMu,      "うぅ…。バタン" },
		{ eAisha, eIkari,   "よし今だ！" },
		{ eEnd, eDefault, nullptr },
	},
	{ 
		{ eYohi,   eKomatta,	"あぁ、龍姫お嬢様、なんとおいたわしい" },
		{ eToko,   eShobon,		"あたしにもっと力があったらあんな人間…" },
		{ eYuyumi, eMu,			"しかし困ったのぅ。龍姫お嬢様が光を食べないと夜が来ん" },
		{ eYuyumi, eMu,			"このまま夜が来ない日が続けばわしらも危ないぞぃ" },
		{ eDakki,  eAseri,		"くっ。このままではお嬢様共々、我らも泡となって消えてしまう…" },
		{ eDakki,  eAseri,		"そうなれば誰がお嬢様をお守りすればいいのだ…" },
		{ eYohi,   eKomatta,    "だから龍姫お嬢様もみんな消えちゃうんですってば" },
		{ eToko,   eShobon,		"完全に錯乱してるな、妲己様…" },
		{ eAisha,  eKomatta,    "あのぉ〜…" },
		{ eYohi,   eIkari,		"！" },
		{ eToko,   eIkari,		"！！" },
		{ eYuyumi, eIkari,		"！！！" },
		{ eDakki,  eIkari,		"！！！！" },
		{ eYohi,   eIkari,		"何しに来たの！！今度こそ私たちの夜を根こそぎ奪いに来たとでも言うの？！" },
		{ eToko,   eIkari,		"ゆるせねぇ…！なんて強欲な人間め！" },
		{ eAisha,  eKomatta,    "ちが…、今度は話し合いをしに…" },
		{ eYuyumi, eIkari,		"問答無用！" },
		{ eDakki,  eIkari,		"龍姫お嬢様に深手を負わせ…あまつさえ止めを刺しに来るとは…" },
		{ eDakki,  eIkari,		"許せぬ…。貴様は我らが全力で叩き潰してやろう！！" },
		{ eAisha,  eKomatta,	"ちょ、ちょっと待ってよー！" },
		{ eAisha,  eDefault,	nullptr },
		{ eYohi,   eKomatta,	"キュ〜…、バタン" },
		{ eToko,   eIkari,		"妖飛！" },
		{ eToko,   eIkari,		"くっそ！ここからはあたしが相手だ！" },
		{ eAisha,  eDefault,	nullptr },
		{ eToko,   eShobon,		"つ、強い…、ガクッ" },
		{ eYuyumi, eIkari,		"濤子までやられたか…" },
		{ eYuyumi, eIkari,		"わしの出番のようじゃの。ここまでじゃ！" },
		{ eAisha,  eDefault,	nullptr },
		{ eYuyumi, eMu,			"うぐぐ…。" },
		{ eDakki,  eIkari,		"お前達はさがっていろ。私が叩き潰す！" },
		{ eAisha,  eDefault,	nullptr },
		{ eAisha,  eDefault,	"ふぅ…" },
		{ eAisha,  eDefault,	"さて龍姫ちゃんはどこかな？" },
		{ eEnd,  eDefault,		nullptr },
	},
	{
		{ eAisha, eMu,      "　" },
		{ eAisha, eDefault, nullptr },
	},
};