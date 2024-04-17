struct Key {
	//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	char key;
	KEYSTATE state = DOWN;
	//If -1, then global to all keyboards
	int deviceId;
	Key(char key, KEYSTATE state = DOWN, int deviceId = -1) : key(key), state(state), deviceId(deviceId) {};
};
enum KEYSTATE {
	DOWN,
	UP,
	CLICK
};