#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

using image = vector<string>;
const int INF = 1e9;

pair<vector<image>, vector<int>> InputImages() {
	int n;
	cin >> n;
	if (n == 0)
		return {};
	vector<image> images(n);
	vector<int> id(n);
	iota(id.begin(), id.end(), 1);
	for (int i = 0; i < n; ++ i) {
		int r, c;
		cin >> r >> c;
		images[i].resize(r);
		getchar();
		for (auto &row : images[i]) {
			getline(cin, row);
			row.resize(c);
		}
	}
	return make_pair(images, id);
}
pair<int, pair<int, int>> Compare(image a, image b) {
	pair<int, pair<int, int>> result(0, make_pair(0, 0));
	for (int dx = -(int)b.size() + 1; dx < (int)a.size(); ++ dx) {
		for (int dy = -(int)b.front().size() + 1; dy < (int)a.front().size(); ++ dy) {
			int score = 0;
			for (int i = max(0, -dx); i < min((int)b.size(), (int)a.size() - dx); ++ i) {
				for (int j = max(0, -dy); j < min((int)b.front().size(), (int)a.front().size() - dy); ++ j) {
					if (b[i][j] != '-' && a[i + dx][j + dy] == b[i][j])
						++ score;
					if (b[i][j] != '-' && a[i + dx][j + dy] != '-' && b[i][j] != a[i + dx][j + dy])
						score = -INF;
				}
			}
			// no need to compare the offset since dx and dy are enumerated increasingly
			if (result.first < score)
				result = {score, make_pair(dx, dy)};
		}
	}
	return result;
}
image Combine(image a, image b, pair<int, int> offset) {
	auto &[dx, dy] = offset;
	int tx = min(0, dx);
	int ty = min(0, dy);
	int nRow = max((int)a.size(), (int)b.size() + dx) - tx;
	int nColumn = max((int)a.front().size(), (int)b.front().size() + dy) - ty;
	image c(nRow, string(nColumn, '-'));
	
	for (int i = 0; i < (int)b.size(); ++ i) {
		for (int j = 0; j < (int)b.front().size(); ++ j) {
			if (b[i][j] != '-') {
				c[i - tx + dx][j - ty + dy] = b[i][j];
			}
		}
	}
	for (int i = 0; i < (int)a.size(); ++ i) {
		for (int j = 0; j < (int)a.front().size(); ++ j) {
			if (a[i][j] != '-') {
				c[i - tx][j - ty] = a[i][j];
			}
		}
	}
	return c;
}

void outputImage(image img, int id) {
	cout << "    MAP " << id << ":\n";
	cout << "    +" << string(img.front().size(), '-') << "+\n";
	for (auto &row : img) {
		cout << "    |" << row << "|\n";
	}
	cout << "    +" << string(img.front().size(), '-') << "+\n";
}

int main() {
    // ios::sync_with_stdio(0); cin.tie(0);

    int T = 1;
	while (true) {
		auto [images, id] = InputImages();
		if (images.empty())
			return 0;
		int nxtId = (int)id.size() + 1;
		while (true) {
			tuple<int, int, int, pair<int, int>> result(0, 0, 0, make_pair(0, 0));
			for (int i = 0; i < (int)images.size(); ++ i) {
				// no need to enumerate j < i since (i, j) and (j, i) yield the same score
				for (int j = i + 1; j < (int)images.size(); ++ j) {
					auto [score, offset] = Compare(images[i], images[j]);
					// no need to compare the sequence number since they are enuerated increasingly
					if (get<0>(result) < score) {
						result = {score, i, j, offset};
					}
				}
			}
			if (get<0>(result) == 0)
				break;
			auto merged_image = Combine(images[get<1>(result)], images[get<2>(result)], get<3>(result));
			images.erase(images.begin() + get<2>(result));
			images.erase(images.begin() + get<1>(result));
			id.erase(id.begin() + get<2>(result));
			id.erase(id.begin() + get<1>(result));
			images.push_back(merged_image);
			id.push_back(nxtId ++);

			/*
			cout << get<0>(result) << " " << get<3>(result).first<< " " << get<3>(result).second << "\n";
			for (int i = 0; i < images.size(); ++ i) {
				if (i != 0)
					cout << "\n";
				outputImage(images[i], id[i]);
			}
			cout << "\n\n";
			*/
		}
		if (T != 1)
			cout << "\n";
		cout << "Case " << T ++ << "\n";
		for (int i = 0; i < (int)images.size(); ++ i) {
			if (i != 0)
				cout << "\n";
			outputImage(images[i], id[i]);
		}
	}
}