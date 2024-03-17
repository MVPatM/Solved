#include <iostream>
#include <algorithm>

int RGBdp[3]; // Red, Green, Blue

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int GetRGBMin();

int main(void) {
	fastio;
	cout << GetRGBMin();

	return 0;
}

int GetRGBMin() {
	int house_num, redC, blueC, greenC;
	cin >> house_num;
	cin >> redC >> blueC >> greenC;
	RGBdp[0] = redC;
	RGBdp[1] = blueC;
	RGBdp[2] = greenC;

	for (int i = 1; i < house_num; i++) {
		cin >> redC >> greenC >> blueC;
		int tmpR, tmpB, tmpG; // redc, greenc, bluec변수를 이용을 하면 된다. 그러면 tmp변수를 만들지 않아도 된다.
		tmpR = min(RGBdp[1], RGBdp[2]) + redC;
		tmpB = min(RGBdp[0], RGBdp[1]) + blueC;
		tmpG = min(RGBdp[0], RGBdp[2]) + greenC;

		RGBdp[0] = tmpR;
		RGBdp[1] = tmpG;
		RGBdp[2] = tmpB;
	}

	return min(RGBdp[0], min(RGBdp[1], RGBdp[2]));
}