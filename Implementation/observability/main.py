import pytest
import logging
import os

from configs.variables import *
from configs.logging_config import configure_logging

# TODO: 
#   -> Tests are supposed to save result metrics in a database
#      - Maybe a local cache to store data while tests are running 
#        (to avoid R/W to database, which can be costly)    

# Configure logging once at the start of the application
configure_logging()

if __name__ == "__main__":
    logging.info("Running tests...")
    os.remove("/app/app_log.log")
    
    exit_code = pytest.main(["-vv", "test_api/"]) 
    logging.info("Finished")
