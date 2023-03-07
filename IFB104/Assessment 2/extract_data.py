from urllib.request import urlopen, Request
from re import findall, finditer
from sqlite3 import *


def downloader(url):
    return urlopen(url)


def zoo_scraper():
    url = "https://www.thezoo.com.au/"
    web_page = downloader(url)
    reg = r"<div.*class=.description.*[\n]+.*?</div>"
    test = fin


if __name__ == "__main__":
    pass
