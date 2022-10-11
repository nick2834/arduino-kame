<template>
	<view class="content">
		<view class="controller">
			<view class="item head flex align-center justify-around">
				<view v-for="item in btnList" class="btn" hover-class="btn-hover" @click="handleClick"
					data-field="top">
					<text class="icon">{{item.title}}</text>
				</view>
			</view>
			<!-- <view class="item head flex align-center justify-center">
				<view class="center btn" hover-class="btn-hover" @click="handleClick" data-field="top">
					<uni-icons class="icon" type="top" size="30"></uni-icons>
				</view>
			</view>
			<view class="item body flex align-center justify-center">
				<view class="vertical btn" hover-class="btn-hover" @click="handleClick" data-field="left">
					<uni-icons class="icon" type="left" size="30"></uni-icons>
				</view>
				<view class="center btn" hover-class="btn-hover" @click="handleClick" data-field="stop">
					暂停
				</view>
				<view class="vertical btn" hover-class="btn-hover" @click="handleClick" data-field="right">
					<uni-icons class="icon" type="right" size="30"></uni-icons>
				</view>
			</view>
			<view class="item body flex align-center justify-center">
				<view class="vertical btn" hover-class="btn-hover" @click="handleClick" data-field="tLeft">
					<uni-icons class="icon" type="arrow-left" size="30"></uni-icons>
				</view>
				<view class="center btn" hover-class="btn-hover" @click="handleClick" data-field="bottom">
					<uni-icons class="icon" type="bottom" size="30"></uni-icons>
				</view>
				<view class="vertical btn" hover-class="btn-hover" @click="handleClick" data-field="tRight">
					<uni-icons class="icon" type="arrow-right" size="30"></uni-icons>
				</view>
			</view> -->
		</view>
		<uni-popup ref="popup" :mask-click="false">
			<text>Popup</text>
			<button @click="close">关闭</button>
		</uni-popup>
	</view>
</template>

<script>
	// https://blog.csdn.net/haduwi/article/details/124422976  tcp插件开发
	export default {
		data() {
			return {
				tcpHost: "192.168.137.1",
				tcpPort: 8266,
				btnList: [{
						title: "左转",
						value: 0
					},
					{
						title: "前进",
						value: 0
					},
					{
						title: "右转",
						value: 0
					},
					{
						title: "向左",
						value: 0
					},
					{
						title: "暂停",
						value: 0
					},
					{
						title: "向右",
						value: 0
					},
					{
						title: "打招呼",
						value: 0
					},
					{
						title: "向右",
						value: 0
					},
					{
						title: "波浪",
						value: 0
					},
				]
			}
		},
		onLoad() {
			// #ifdef APP-PLUS
			this.initScoket()
			// #endif
		},
		methods: {
			handleClick: function(e) {
				const {
					dataset: {
						field
					}
				} = e.currentTarget;
				console.log(field)
				// this.$refs.popup.open('center')
				// #ifdef APP-PLUS
				this.initScoket(field)
				// #endif
			},
			initScoket(text) {
				const _this = this;
				if (plus.os.name == "Android") {
					const PrintWriter = plus.android.importClass("java.io.PrintWriter");
					const BufferedWriter = plus.android.importClass("java.io.BufferedWriter");
					const OutputStreamWriter = plus.android.importClass("java.io.OutputStreamWriter");
					const BufferedReader = plus.android.importClass("java.io.BufferedReader");
					const InputStreamReader = plus.android.importClass("java.io.InputStreamReader");
					const Socket = plus.android.importClass("java.net.Socket");
					//测试改良 
					const StrictMode = plus.android.importClass("android.os.StrictMode");
					const Build = plus.android.importClass("android.os.Build");
					if (Build.VERSION.SDK_INT > 9) {
						var policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
						StrictMode.setThreadPolicy(policy);
					}
					uni.showLoading({
						title: "链接服务器中"
					})
					var socket = new Socket(_this.tcpHost, _this.tcpPort);
					socket.setSoTimeout(5000);
					uni.hideLoading()
					// 字节流通向字符流的桥梁
					var inputStreamReader = new InputStreamReader(socket.getInputStream());
					//  从字符输入流中读取文本
					var socketReader = new BufferedReader(inputStreamReader);
					// 从字符流桥接字节流
					var outputStreamWriter = new OutputStreamWriter(socket.getOutputStream());
					var bufferWriter = new BufferedWriter(outputStreamWriter);
					// 创建一个文件并向文本文件写入数据
					var socketWriter = new PrintWriter(bufferWriter, true);
					socketWriter.println(text || "连接成功");
					var msgBeReceived = socketReader.readLine();
					console.log('读取信息', msgBeReceived);
					socket.close()
				}
			},
			sendMessage(text) {
				if (plus.os.name == "Android") {
					const PrintWriter = plus.android.importClass("java.io.PrintWriter");
					const BufferedWriter = plus.android.importClass("java.io.BufferedWriter");
					const OutputStreamWriter = plus.android.importClass("java.io.OutputStreamWriter");
					const BufferedReader = plus.android.importClass("java.io.BufferedReader");
					const InputStreamReader = plus.android.importClass("java.io.InputStreamReader");
					// 字节流通向字符流的桥梁
					var inputStreamReader = new InputStreamReader(this.socket.getInputStream());
					//  从字符输入流中读取文本
					var socketReader = new BufferedReader(inputStreamReader);
					// 从字符流桥接字节流
					var outputStreamWriter = new OutputStreamWriter(this.socket.getOutputStream());
					var bufferWriter = new BufferedWriter(outputStreamWriter);
					// 创建一个文件并向文本文件写入数据
					var socketWriter = new PrintWriter(bufferWriter, true);
					socketWriter.println(text);
					var msgBeReceived = socketReader.readLine();
					console.log('读取信息', msgBeReceived);
				}
			}
		}
	}
</script>

<style lang="scss">
	.content {
		background-color: #efeeee;
		height: 100vh;
	}

	.controller {
		padding: 20rpx 20px;

		.item {
			padding-bottom: 40rpx;
			flex-wrap: wrap;
		}

		.btn {
			width: 180rpx;
			height: 100rpx;
			box-shadow: 36rpx 36rpx 60rpx rgba(0, 0, 0, 0.1),
				-36rpx -36rpx 60rpx rgba(255, 255, 255, 1);
			border-radius: 20rpx;
			display: flex;
			align-items: center;
			justify-content: center;
			background: #efeeee;
			transition: box-shadow .2s ease-out;
			position: relative;
			margin-bottom: 80rpx;
			.icon {
				color: #0052d9 !important;
			}

			&.center {
				margin: 0 60rpx;
			}

			&.btn-hover {
				box-shadow: 0 0 0 rgba(0, 0, 0, 0.1),
					0 0 0 rgba(255, 255, 255, 1),
					inset 36rpx 36rpx 60rpx rgba(0, 0, 0, 0.1),
					inset -36rpx -36rpx 60rpx rgba(255, 255, 255, 1);
				/*内嵌投影值*/
				transition: box-shadow .1s ease-out;

				.icon {
					color: #108ee9 !important;
					font-size: 28rpx !important;
					transition: font-size .1s ease-out;
				}
			}
		}
	}
</style>
