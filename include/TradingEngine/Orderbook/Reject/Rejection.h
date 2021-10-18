#pragma once
#include "TradingEngine/Orders/OrderCore.h"

namespace TradingEngine::Orderbook::Reject {
	enum class rejectionReason
	{
		Unkown,
		OrderNotFound,
		OrderIdAlreadyPresent,
		InstrumentNotFound,
		AttemptingToModifyWrongSide,
		ModifyOrderDoesntModifyAnything
	};

	class Rejection
	{
	public:
		Rejection(Orders::OrderCore rejectedOrder, rejectionReason rr);

		Reject::rejectionReason getRejectionReason();
		Orders::OrderCore getOrderCore();
		Rejection& operator=(const Rejection& rhs)
		{
			rr_ = rhs.rr_;
			orderBase_ = rhs.orderBase_;
			return *this;
		}

	private:
		rejectionReason rr_;
		Orders::OrderCore orderBase_;

	};
}
