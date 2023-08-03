export const getStringLs = (key) => localStorage.getItem(key);
export const setStringLs = (key, value) => localStorage.setItem(key, value);
export const getObjectLs = (key) => JSON.parse(getStringLs(key));
export const setObjectLs = (key, value) =>
  setStringLs(key, JSON.stringify(value));
export const removeItemLs = (key) => localStorage.removeItem(key);
