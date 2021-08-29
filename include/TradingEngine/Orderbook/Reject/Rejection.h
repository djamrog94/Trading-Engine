#pragma once
namespace TradingEngine::Orderbook::Reject {
	enum class rejectionReason
	{
		Unkown,
		OrderNotFound,
		InstrumentNotFound,
		AttemptingToModifyWrongSide
	};

	class Rejection
	{
	public:
		Rejection(long roid, rejectionReason rr);

		Reject::rejectionReason getRejectionReason();
		long getRejectedOrderId();

	private:
		rejectionReason rr_;
		long roid_;

	};
}
