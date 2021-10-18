#include "TradingEngine/Orderbook/Reject/RejectCreator.h"
namespace TradingEngine::Orderbook::Reject {
	Rejection RejectCreator::generateOrderCoreReject(Orders::OrderCore oc, Reject::rejectionReason rr)
	{
		Rejection newRej = Rejection(oc, rr);
		return newRej;
	}
}
