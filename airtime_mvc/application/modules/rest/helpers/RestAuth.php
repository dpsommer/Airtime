<?php

class RestAuth
{
	public function verifyAuth($checkApiKey, $checkSession)
	{
		//Session takes precedence over API key for now:
		if ($checkSession && $this->verifySession())
		{
			return true;
		}
	
		if ($checkApiKey && $this->verifyAPIKey())
		{
			return true;
		}
	
		$resp = $this->getResponse();
		$resp->setHttpResponseCode(401);
		$resp->appendBody("ERROR: Incorrect API key.");
			
		return false;
	}
	
	public function getOwnerId()
	{
		try {
			if ($this->verifySession()) {
				$service_user = new Application_Service_UserService();
				return $service_user->getCurrentUser()->getDbId();
			} else {
				$defaultOwner = CcSubjsQuery::create()
									->filterByDbType('A')
									->orderByDbId()
									->findOne();
				if (!$defaultOwner) {
					// what to do if there is no admin user?
					// should we handle this case?
					return null;
				}
				return $defaultOwner->getDbId();
			}
		} catch(Exception $e) {
			Logging::info($e->getMessage());
		}
	}
	
	private function verifySession()
	{
		$auth = Zend_Auth::getInstance();
		if ($auth->hasIdentity())
		{
			return true;
		}
		return false;
	}
	
	private function verifyAPIKey()
	{
		//The API key is passed in via HTTP "basic authentication":
		// http://en.wikipedia.org/wiki/Basic_access_authentication
		$CC_CONFIG = Config::getConfig();
	
		//Decode the API key that was passed to us in the HTTP request.
		$authHeader = $this->getRequest()->getHeader("Authorization");
		$encodedRequestApiKey = substr($authHeader, strlen("Basic "));
		$encodedStoredApiKey = base64_encode($CC_CONFIG["apiKey"][0] . ":");
	
		if ($encodedRequestApiKey === $encodedStoredApiKey)
		{
			return true;
		} else {
			return false;
		}
	
		return false;
	}
	
}