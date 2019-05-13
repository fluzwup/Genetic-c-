#include <cstdlib>
#include <cstdio>
#include <cstring>

const char *dictionary[] =
{
	"A", "ABLE", "ABOUT", "ABOVE", "ACT", "ADD", "AFTER", "AGAIN", "AGAINST", "AGE", "AGO",
	"AIR", "ALL", "ALSO", "ALWAYS", "AM", "AMONG", "AN", "AND", "ANIMAL", "ANSWER", "ANY",
	"APPEAR", "ARE", "AREA", "AS", "ASK", "AT", "BACK", "BASE", "BE", "BEAUTY", "BED",
	"BEEN", "BEFORE", "BEGAN", "BEGIN", "BEHIND", "BEST", "BETTER", "BETWEEN", "BIG",
	"BIRD", "BLACK", "BLUE", "BOAT", "BODY", "BOOK", "BOTH", "BOX", "BOY", "BRING", "BROUGHT",
	"BUILD", "BUSY", "BUT", "BY", "CALL", "CAME", "CAN", "CAR", "CARE", "CARRY", "CAUSE",
	"CENTER", "CERTAIN", "CHANGE", "CHECK", "CHILDREN", "CITY", "CLASS", "CLEAR", "CLOSE",
	"COLD", "COLOR", "COME", "COMMON", "COMPLETE", "CONTAIN", "CORRECT", "COULD", "COUNTRY",
	"COURSE", "COVER", "CROSS", "CRY", "CUT", "DARK", "DAY", "DECIDE", "DEEP", "DEVELOP",
	"DID", "DIFFER", "DIRECT", "DO", "DOES", "DOG", "DONE", "DOOR", "DOWN",
	"DRAW", "DRIVE", "DRY", "DURING", "EACH", "EARLY", "EARTH", "EASE", "EAST", "EAT",
	"END", "ENOUGH", "EVEN", "EVER", "EVERY", "EXAMPLE", "EYE", "FACE", "FACT", "FALL",
	"FAMILY", "FAR", "FARM", "FAST", "FATHER", "FEEL", "FEET", "FEW", "FIELD", "FIGURE",
	"FILL", "FINAL", "FIND", "FINE", "FIRE", "FIRST", "FISH", "FIVE", "FLY", "FOLLOW",
	"FOOD", "FOOT", "FOR", "FORCE", "FORM", "FOUND", "FOUR", "FREE", "FRIEND", "FROM",
	"FRONT", "FULL", "GAME", "GAVE", "GET", "GIRL", "GIVE", "GO", "GOLD", "GOOD", "GOT",
	"GOVERN", "GREAT", "GREEN", "GROUND", "GROUP", "GROW", "HAD", "HALF", "HAND", "HAPPEN",
	"HARD", "HAS", "HAVE", "HE", "HEAD", "HEAR", "HEARD", "HEAT", "HELP", "HER", "HERE",
	"HIGH", "HIM", "HIS", "HOLD", "HOME", "HORSE", "HOT", "HOUR", "HOUSE", "HOW", "HUNDRED",
	"I", "IDEA", "IF", "IN", "INCH", "INTEREST", "IS", "ISLAND", "IT", "JUST", "KEEP",
	"KIND", "KING", "KNEW", "KNOW", "LAND", "LANGUAGE", "LARGE", "LAST", "LATE", "LAUGH",
	"LAY", "LEAD", "LEARN", "LEAVE", "LEFT", "LESS", "LET", "LETTER", "LIFE", "LIGHT",
	"LIKE", "LINE", "LIST", "LISTEN", "LITTLE", "LIVE", "LONG", "LOOK", "LOT", "LOVE",
	"LOW", "MACHINE", "MADE", "MAIN", "MAKE", "MAN", "MANY", "MAP", "MARK", "MAY", "ME",
	"MEAN", "MEASURE", "MEN", "MIGHT", "MILE", "MIND", "MINUTE", "MISS", "MONEY", "MOON",
	"MORE", "MORNING", "MOST", "MOTHER", "MOUNTAIN", "MOVE", "MUCH", "MUSIC", "MUST",
	"MY", "NAME", "NEAR", "NEED", "NEVER", "NEW", "NEXT", "NIGHT", "NO", "NORTH", "NOTE",
	"NOTHING", "NOTICE", "NOUN", "NOW", "NUMBER", "NUMERAL", "OBJECT", "OF", "OFF", "OFTEN",
	"OH", "OLD", "ON", "ONCE", "ONE", "ONLY", "OPEN", "OR", "ORDER", "OTHER", "OUR",
	"OUT", "OVER", "OWN", "PAGE", "PAPER", "PART", "PASS", "PATTERN", "PEOPLE", "PERHAPS",
	"PERSON", "PICTURE", "PIECE", "PLACE", "PLAIN", "PLAN", "PLANE", "PLANT", "PLAY",
	"POINT", "PORT", "POSE", "POSSIBLE", "POUND", "POWER", "PRESS", "PROBLEM", "PRODUCE",
	"PRODUCT", "PULL", "PUT", "QUESTION", "QUICK", "RAIN", "RAN", "REACH", "READ", "READY",
	"REAL", "RECORD", "RED", "REMEMBER", "REST", "RIGHT", "RIVER", "ROAD", "ROCK", "ROOM",
	"ROUND", "RULE", "RUN", "SAID", "SAME", "SAW", "SAY", "SCHOOL", "SCIENCE", "SEA",
	"SECOND", "SEE", "SEEM", "SELF", "SENTENCE", "SERVE", "SET", "SEVERAL", "SHAPE",
	"SHE", "SHIP", "SHORT", "SHOULD", "SHOW", "SIDE", "SIMPLE", "SINCE", "SING", "SIT",
	"SIX", "SIZE", "SLEEP", "SLOW", "SMALL", "SNOW", "SO", "SOME", "SONG", "SOON", "SOUND",
	"SOUTH", "SPECIAL", "SPELL", "STAND", "STAR", "START", "STATE", "STAY", "STEP", "STILL",
	"STOOD", "STOP", "STORY", "STREET", "STRONG", "STUDY", "SUCH", "SUN", "SURE", "SURFACE",
	"TABLE", "TAIL", "TAKE", "TALK", "TEACH", "TELL", "TEN", "TEST", "THAN", "THAT",
	"THE", "THEIR", "THEM", "THEN", "THERE", "THESE", "THEY", "THING", "THINK", "THIS",
	"THOSE", "THOUGH", "THOUGHT", "THOUSAND", "THREE", "THROUGH", "TIME", "TO", "TOGETHER",
	"TOLD", "TOO", "TOOK", "TOP", "TOWARD", "TOWN", "TRAVEL", "TREE", "TRUE", "TRY",
	"TURN", "TWO", "UNDER", "UNIT", "UNTIL", "UP", "US", "USE", "USUAL", "VERY", "VOICE",
	"VOWEL", "WAIT", "WALK", "WANT", "WAR", "WARM", "WAS", "WATCH", "WATER", "WAY", "WE",
	"WEEK", "WEIGHT", "WELL", "WENT", "WERE", "WEST", "WHAT", "WHEEL", "WHEN", "WHERE",
	"WHICH", "WHILE", "WHITE", "WHO", "WHOLE", "WHY", "WILL", "WIND", "WITH", "WONDER",
	"WOOD", "WORD", "WORK", "WORLD", "WOULD", "WRITE", "YEAR", "YES", "YET", "YOU", "YOUNG",
	"YOUR"
};

bool IsAWord(const char *word, int start, int end)
{
	int index = (start + end) / 2;
	int val = strcmp(word, dictionary[index]);

	if(val == 0) return true;

	if(start >= end) return false;

	if(val < 0)
		return IsAWord(word, start, index - 1);
	else
		return IsAWord(word, index + 1, end);
}

bool IsAWord(const char *word)
{
	static int wordcount = sizeof(dictionary) / sizeof(char *);
	return IsAWord(word, 0, wordcount - 1);
}

/*
int main(int argc, char **argv)
{
	printf("%s\n", IsAWord("GARGLEPLEX") ? "true" : "false");
	for(int i = sizeof(dictionary) / sizeof(char *) - 1; i >= 0; --i)
	{
		if(!IsAWord(dictionary[i]))
			printf("Didn't find %i %s\n", i, dictionary[i]);
	}
	return 0;
}
*/
