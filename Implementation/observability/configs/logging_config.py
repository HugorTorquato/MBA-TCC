# configs/logging_config.py

import logging

def configure_logging():
    """
    Configure the logging for the application. This will set the logging level,
    format, and handlers for both console and file output.
    """
    logging.basicConfig(
        level=logging.INFO,  # Set log level (can be DEBUG, INFO, WARNING, ERROR)
        format="%(asctime)s [%(levelname)s] %(message)s",  # Log format
        handlers=[
            logging.StreamHandler(),        # Print to console
            logging.FileHandler("app_log.log")  # Save to a file
        ]
    )
    
    # Optionally, you could add specific loggers for different modules or use cases
    # logging.getLogger("[SomeModule]")

