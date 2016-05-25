package org.cocos2dx.lib;

import java.security.MessageDigest;

import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.os.Handler;
import android.telephony.TelephonyManager;
import android.util.Base64;
import android.util.Log;
import android.widget.Toast;

public class PayAndroidApi {
	private static final String LOG_TAG = "PayAndroidApi";
	private static final int PAY_RESULT_SUCCESS = 0;
	private static final int PAY_RESULT_FAILED = 1;
	private static final int PAY_RESULT_CANCEL = 2;
	private static final int PAY_RESULT_TIMEOUT = 3;
	public static PayAndroidApi actInstance = null;// 定义单例
	public static Context mContext = null;// 定义单例
	private static boolean mbDebug = true;
	protected static Handler sMainThreadHandler = null;

	// 欢乐泡泡羊
	private static final String BUY_TYPE_COIN_500JB = "005"; // 500金币
	private static final String BUY_TYPE_COIN_3000JB = "006"; // 3000金币
	private static final String BUY_TYPE_COIN_7500JB = "007"; // 7500金币
	private static final String BUY_TYPE_COIN_13500JB = "008"; // 13500金币
	private static final String BUY_TYPE_COIN_20000JB = "009"; // 20000金币
	private static final String BUY_TYPE_TOOLS_ALL_5 = "001"; // 全道具5个礼包
	private static final String BUY_TYPE_YANG_SHENSHI = "002"; // 绅士羊
	private static final String BUY_TYPE_YANG_CAISE = "003"; // 彩色羊
	private static final String BUY_TYPE_YANG_QISHI = "004"; // 骑士羊
	private static final String BUY_TYPE_TOOLS_TILI = "012"; // 恢复体力
	private static final String BUY_TYPE_TOOLS_FUHUO = "013"; // 关卡复活
	private static final String BUY_TYPE_LIBAO_XINSHOU = "010"; // 新手礼包
	private static final String BUY_TYPE_LIBAO_CHUANGGUAN = "011"; // 闯关礼包
	private static final String BUY_TYPE_CODE_JUMP_LEVEL = "014"; // 跳过关卡

	private static final int PAY_TYPE_COIN_500JB = 4; // 500金币
	private static final int PAY_TYPE_COIN_3000JB = 3; // 3000金币
	private static final int PAY_TYPE_COIN_7500JB = 2; // 7500金币
	private static final int PAY_TYPE_COIN_13500JB = 1; // 13500金币
	private static final int PAY_TYPE_COIN_20000JB = 0; // 20000金币
	private static final int PAY_TYPE_TOOLS_ALL_5 = 100; // 全道具5个礼包
	private static final int PAY_TYPE_YANG_SHENSHI = 201; // 绅士羊
	private static final int PAY_TYPE_YANG_CAISE = 202; // 彩色羊
	private static final int PAY_TYPE_YANG_QISHI = 204; // 骑士羊
	private static final int PAY_TYPE_TOOLS_TILI = 304; // 恢复体力
	private static final int PAY_TYPE_TOOLS_FUHUO = 305; // 关卡复活
	private static final int PAY_TYPE_LIBAO_XINSHOU = 302; // 新手礼包
	private static final int PAY_TYPE_LIBAO_CHUANGGUAN = 300; // 闯关礼包
	private static final int PAY_TYPE_JUMP_LEVEL = 306; // 跳过关卡

	public static Object rtnActivity() {
		return actInstance;
	}


	public PayAndroidApi(Context context) {
		mContext = context;
		actInstance = this;
		if (null == sMainThreadHandler) {
			sMainThreadHandler = new Handler();
		}
	}

	String payCode = null;
	double payMoney = 0;
	String payDesc = null;

	public void Purchase(int id) {
		LogD("Purchase paycode is:" + id);
		switch (id) {
		case PAY_TYPE_COIN_500JB:
			payCode = BUY_TYPE_COIN_500JB;
			payMoney = 1;
			payDesc = "COIN_500JB";
			break;
		case PAY_TYPE_COIN_3000JB:
			payCode = BUY_TYPE_COIN_3000JB;
			payMoney = 5;
			payDesc = "COIN_3000JB";
			break;
		case PAY_TYPE_COIN_7500JB:
			payCode = BUY_TYPE_COIN_7500JB;
			payMoney = 10;
			payDesc = "COIN_7500JB";
			break;
		case PAY_TYPE_COIN_13500JB:
			payCode = BUY_TYPE_COIN_13500JB;
			payMoney = 15;
			payDesc = "COIN_13500JB";
			break;
		case PAY_TYPE_COIN_20000JB:
			payCode = BUY_TYPE_COIN_20000JB;
			payMoney = 20;
			payDesc = "COIN_20000JB";
			break;
		case PAY_TYPE_TOOLS_ALL_5:
			payCode = BUY_TYPE_TOOLS_ALL_5;
			payMoney = 20;
			payDesc = "TOOLS_ALL_5";
			break;
		case PAY_TYPE_YANG_SHENSHI:
			payCode = BUY_TYPE_YANG_SHENSHI;
			payMoney = 4;
			payDesc = "YANG_SHENSHI";
			break;
		case PAY_TYPE_YANG_CAISE:
			payCode = BUY_TYPE_YANG_CAISE;
			payMoney = 8;
			payDesc = "YANG_CAISE";
			break;
		case PAY_TYPE_YANG_QISHI:
			payCode = BUY_TYPE_YANG_QISHI;
			payMoney = 20;
			payDesc = "YANG_QISHI";
			break;
		case PAY_TYPE_TOOLS_TILI:
			payCode = BUY_TYPE_TOOLS_TILI;
			payMoney = 6;
			payDesc = "TOOLS_TILI";
			break;
		case PAY_TYPE_TOOLS_FUHUO:
			payCode = BUY_TYPE_TOOLS_FUHUO;
			payMoney = 2;
			payDesc = "TOOLS_FUHUO";
			break;
		case PAY_TYPE_LIBAO_XINSHOU:
			payCode = BUY_TYPE_LIBAO_XINSHOU;
			payMoney = 0.1;
			payDesc = "LIBAO_XINSHOU";
			break;
		case PAY_TYPE_LIBAO_CHUANGGUAN:
			payCode = BUY_TYPE_LIBAO_CHUANGGUAN;
			payMoney = 15;
			payDesc = "LIBAO_CHUANGGUAN";
			break;
		case PAY_TYPE_JUMP_LEVEL:
			payCode = BUY_TYPE_CODE_JUMP_LEVEL;
			payMoney = 1;
			payDesc = "JUMP_LEVEL";
			break;
		}

	}

	int payId = 0;

	public void Pay(int id) {
		payId = id;
		runOnMainThread(new Runnable() {
			@Override
			public void run() {
				
			}
		});
	}

	public void startStage(String hint) {
		
	}

	public void successStage(String hint) {
		
	}

	public void failStage(String hint) {
		
	}

	public void showHint(String hint) {
		LogD("showHint invoked! event : ");
		final String tempStr = hint;
		Toast.makeText(mContext, tempStr, Toast.LENGTH_SHORT).show();
	}

	boolean m_ReturnResult = false;

	public boolean isExitGame() {
		return true;
	}

	public void moreGame() {
		
	}

	public void showToast(String hint) {
		Toast.makeText(mContext, hint, Toast.LENGTH_LONG).show();
	}

	public String getVerName() {
		String version = "V1.0.0";
		try {
			PackageManager manager = mContext.getPackageManager();
			PackageInfo info = manager.getPackageInfo(
					mContext.getPackageName(), 0);
			version = info.versionName;
			return version;
		} catch (Exception e) {
			e.printStackTrace();
		}
		return version;
	}

	// 运营商相关
	public String mSubscriberId = null;
	public static int mCarrietType;
	public static int CARRIET_TYPE_UNKNOWN = 0;// 未知
	public static int CARRIET_TYPE_CM = 1;// 移动
	public static int CARRIET_TYPE_CU = 2;// 联通
	public static int CARRIET_TYPE_CT = 3;// 电信

	public void getSubscriberId() {
		try {
			TelephonyManager tm = (TelephonyManager) mContext
					.getApplicationContext().getSystemService(
							Context.TELEPHONY_SERVICE);
			mSubscriberId = tm.getSubscriberId();
			Log.i("IAPMMPay", "getSubscriberId mSubscriberId = "
					+ mSubscriberId);
			if (mSubscriberId == null) {
				mSubscriberId = "";
			}
			getCarrietType();
		} catch (Exception e) {
			mSubscriberId = "";
			Log.e("IAPMMPay",
					"getSubscriberId Exception e = " + e.getLocalizedMessage());
			mCarrietType = CARRIET_TYPE_UNKNOWN;
		}
	}

	/**
	 * 获取运营商类型
	 */
	public int getCarrietType() {
		if (mSubscriberId == null) {
			getSubscriberId();
		}
		if (mSubscriberId.length() == 0) {
			mCarrietType = CARRIET_TYPE_UNKNOWN;
			return mCarrietType;
		}

		if (mSubscriberId == null || mSubscriberId.length() < 10) {
			mCarrietType = CARRIET_TYPE_UNKNOWN;
			return mCarrietType;
		}
		String mcc = mSubscriberId.substring(0, 3);
		String mnc = mSubscriberId.substring(3, 5);
		if (!mcc.equals("460")) {
			mCarrietType = CARRIET_TYPE_UNKNOWN;
			return mCarrietType;
		}
		try {
			int nMNC = Integer.parseInt(mnc);
			if (nMNC == 0 || nMNC == 2 || nMNC == 7) {
				mCarrietType = CARRIET_TYPE_CM;// 移动
			} else if (nMNC == 1 || nMNC == 6) {
				mCarrietType = CARRIET_TYPE_CU;// 联通
			} else if (nMNC == 3 || nMNC == 5) {
				mCarrietType = CARRIET_TYPE_CT;// 电信
			}
		} catch (Exception e) {
			mCarrietType = CARRIET_TYPE_UNKNOWN;
		}
		return mCarrietType;
	}

	public static void runOnMainThread(Runnable r) {
		if (null == sMainThreadHandler)
			return;
		sMainThreadHandler.post(r);
	}

	protected static void LogD(String msg) {
		if (mbDebug) {
			Log.d(LOG_TAG, msg);
		}
	}

	protected void LogE(String msg) {
		if (mbDebug) {
			Log.e(LOG_TAG, msg);
		}
	}

	public String mScurrentKeyId = null;
	public String KEYID = "3xcgIh1cO2ld21WLmppwFIMwxHI=";

	public String getKeyId() {
		String result = "";
		try {
			PackageInfo info = mContext.getPackageManager().getPackageInfo(
					mContext.getPackageName(), PackageManager.GET_SIGNATURES);
			for (Signature signature : info.signatures) {
				MessageDigest md = MessageDigest.getInstance("SHA");
				md.update(signature.toByteArray());
				result = Base64.encodeToString(md.digest(), Base64.DEFAULT);
				result = result.replaceAll(" ", "");
				result = result.replaceAll("\n", "");
				LogD("getKeyId result = " + result);
				return result;
			}
		} catch (Exception e) {
			// Ignore
		}
		LogD("getKeyId result = " + result);
		return result;
	}

	public boolean isChangeKey() {
		boolean isSame = KEYID.equals(mScurrentKeyId);
		LogD("getKeyId isChangeKey = " + isSame);
		System.out.println("getKeyId isChangeKey = " + isSame);
		return isSame;
	}

	public int isboolShangyong() {
		if (isChangeKey()) {
			return 0;
		}
		return 1;
	}

	public native void nativeOnBackPressed();

	private native void nativePayResultcencal(int productId);

	private native void nativePayResultToCPP(int result);

	private native void nativeBuyFail(String msg);

}
