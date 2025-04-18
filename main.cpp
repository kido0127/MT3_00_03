#include <Novice.h>

const char kWindowTitle[] = "MT3_00_03";
struct Matrix4x4
{
	float m[4][4];
};
struct Vector3 {
	float x, y, z;
};
//1.平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 matrix = {};
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	matrix.m[3][0] = translate.x;
	matrix.m[3][1] = translate.y;
	matrix.m[3][2] = translate.z;
	return matrix;
};
//2.拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 matrix = {};
	matrix.m[0][0] = scale.x;
	matrix.m[1][1] = scale.y;
	matrix.m[2][2] = scale.z;
	matrix.m[3][3] = 1.0f;
	return matrix;
};
// 3. 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];
	return result;
}



static const int kColuwidth = 60;
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%0.2f", vector.x);
	Novice::ScreenPrintf(x + kColuwidth, y, "%0.2f", vector.y);
	Novice::ScreenPrintf(x + kColuwidth * 2, y, "%0.2f", vector.z);
	Novice::ScreenPrintf(x + kColuwidth * 3, y, "%s", label);
}
static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	// 最初にラベルを表示
	Novice::ScreenPrintf(x, y, "%s", label);

	// 次の行から数値を表示
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Novice::ScreenPrintf(x + j * kColumnWidth, y + (i + 1) * kRowHeight, "%6.02f", matrix.m[i][j]);
		}
	}
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 translate{ 4.1f,2.6f,0.8f };
	Vector3 scale{ 1.5f,5.2f,7.3f };
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Vector3 point{ 2.3f,3.8f,1.4f };
	Matrix4x4 transformMatrix = {
	1.0f,2.0f,3.0f,4.0f,
	3.0f,1.0f,1.0f,2.0f,
	1.0f,4.0f,2.0f,3.0f,
	2.0f,2.0f,1.0f,3.0f
	};
	Vector3 transformed = Transform(point, transformMatrix);

	

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		VectorScreenPrintf(0, 0, transformed, "transformed");
		MatrixScreenPrintf(0, 20, translateMatrix, "translateMatrix");
		MatrixScreenPrintf(0, 20 +kRowHeight*5, scaleMatrix, "scaleMatrix");
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
