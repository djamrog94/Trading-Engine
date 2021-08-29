#include "TradingEngine/Orderbook/Reject/RejectCreator.h"
namespace TradingEngine::Orderbook::Reject {
	Rejection RejectCreator::generateModyifyRejection(Orders::ModifyOrder mo, Reject::rejectionReason rr)
	{
		Rejection newRej = Rejection(mo.getOrderId(), rr);
		return newRej;
	}
}
