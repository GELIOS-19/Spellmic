from spellmic.spellmic.apps.words.app.utils.formats import Formats


class WordNotFound(Exception):
    """
    Exception raised when a word is not found

    Attributes:
        _word_soup : BeautifulSoup
            the soup object of all the code

    Properties:
        word : str
            the word that was not found
        related_queries : list
            related queries to the word that was not found
    """

    def __init__(self, word_soup):
        self._word_soup = word_soup
        if self._check(): raise self

    def _check(self):
        """Tells if the exception should be raised"""
        error_one = True if self._word_soup.find(attrs={"class": "mispelled-word"}) is not None else False  # misspelled word
        error_two = True if self._word_soup.find(attrs={"class": "words_fail_us_cont"}) is not None else False  # word not in dictionary
        return error_one or error_two

    @property
    def word(self):
        """The word that was not found"""
        spelling_text_tag = self._word_soup.find(attrs={"class": "mispelled-word"})
        return Formats.SpellingFormats.misspelled_spelling_format(spelling_text_tag.text) if spelling_text_tag is not None else None

    @property
    def related_queries(self):
        """Similar queries to the word that was not found"""
        related_queries = []
        spelling_suggestion_text_tags = self._word_soup.find(attrs={"class": "spelling-suggestions"})
        for spelling_suggestion_text_tag in spelling_suggestion_text_tags: related_queries.append(spelling_suggestion_text_tag.text)
        return related_queries

    def __str__(self):
        if len(self.related_queries) > 1: return f"""The word \"{self.word}\" was not found. A few related queries were {Formats.MiscellaneousFormats.neat_list_format(str(self.related_queries[:-1]), format_quotes={"Apostrophe": {"Format": True, "Replacement": '"'}, "Quotation": {"Format": False, "Replacement": ""}})} and "{self.related_queries[-1]}"."""
        elif len(self.related_queries) > 0: return f"The word \"{self.word}\" was not found. A related query was \"{self.related_queries[0]}\"."
        else: return f"The word \"{self.word}\" was not found. No related queries were found."
