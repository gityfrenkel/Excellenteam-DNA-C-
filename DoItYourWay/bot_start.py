import logging

from telegram.ext import CommandHandler
from telegram.ext import MessageHandler, Filters
from telegram.ext import Updater

import BotSettings

logging.basicConfig(
   format='[%(levelname)s %(asctime)s %(module)s:%(lineno)d] %(message)s',
   level=logging.INFO)

logger = logging.getLogger(__name__)

updater = Updater(token=BotSettings.BOT_TOKEN)
dispatcher = updater.dispatcher


def start(bot, update):
   chat_id = update.message.chat_id
   logger.info(f"> Start chat #{chat_id}")
   bot.send_message(chat_id=chat_id, text="Welcome to the  bot!!\nopen the camera and take your way")


def respond(bot, update):
   chat_id = update.message.chat_id
   text = update.message.text
   logger.info(f"= Got on chat #{chat_id}: {text!r}")
   response = text.replace("7", ":bomb:")
   bot.send_document(chat_id=chat_id, document=open('tests/test.zip', 'rb'))
   bot.send_message(chat_id=update.message.chat_id, text=response)

def on_location(bot, update):
   chat_id = update.message.chat_id
   loc = update.message.location
   logger.info(f"& Got location on chat #{chat_id}: {loc!r}")

def description(bot, update):
    chat_id = update.message.chat_id


start_handler = CommandHandler('start', start)
dispatcher.add_handler(start_handler)

start_handler = CommandHandler('description', description)
dispatcher.add_handler(start_handler)

echo_handler = MessageHandler(Filters.text, respond)
dispatcher.add_handler(echo_handler)


dispatcher.add_handler(MessageHandler(Filters.location, on_location))

logger.info("Start polling")
updater.start_polling()