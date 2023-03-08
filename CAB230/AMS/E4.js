function searchBooks(library, authorName) {
    let books = library.filter(a => a.author === authorName)
    if (books.length === 0) return "NOT FOUND"
    return books.map(b => b.title).join()
}