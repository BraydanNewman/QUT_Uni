import { getObjectLs, removeItemLs, setObjectLs } from "./localStorage";
import { useNavigate } from "react-router-dom";
import { useContext } from "react";
import { EmailContext } from "../App";

const authUrl = "http://sefdb02.qut.edu.au:3000/user";

export const registerUser = (
  email,
  password,
  handelRegisterSuccess,
  handelRegisterError
) => {
  fetch(`${authUrl}/register`, {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: "" + JSON.stringify({ email: email, password: password }),
  })
    .then((res) => res.json())
    .then((data) => {
      if ("error" in data) handelRegisterError(data);
      else {
        handelRegisterSuccess();
      }
    });
};

export const loginUser = (
  email,
  password,
  handelTokenData,
  handelLoginError
) => {
  fetch(`${authUrl}/login`, {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body:
      "" +
      JSON.stringify({ email: email, password: password, longExpiry: false }),
  })
    .then((res) => res.json())
    .then((data) => {
      if ("error" in data) handelLoginError(data);
      else handelTokenData(data);
    });
};

export const refreshBearerToken = async (refreshErrorCallback) => {
  let refreshToken = getObjectLs("refreshToken");
  refreshToken = refreshToken ? refreshToken.token : refreshToken;
  await fetch(`${authUrl}/refresh`, {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: "" + JSON.stringify({ refreshToken: refreshToken }),
  })
    .then((res) => {
      switch (res.status) {
        case 400:
          throw Error("Could Not Authenticate Please Login");
        case 401:
          throw Error("Session Has Expired Please Login Again");
        default:
          return res.json();
      }
    })
    .then((data) => {
      if ("error" in data) throw Error(data.message);
      else {
        setObjectLs("bearerToken", data["bearerToken"]);
        setObjectLs("refreshToken", data["refreshToken"]);
      }
    })
    .catch((e) => {
      refreshErrorCallback(e);
    });
};

export const logout = (logoutCallback) => {
  let refreshToken = getObjectLs("refreshToken");
  refreshToken = refreshToken ? refreshToken.token : refreshToken;
  fetch(`${authUrl}/logout`, {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: "" + JSON.stringify({ refreshToken: refreshToken }),
  }).then(() => {
    clearAuthenticationTokens();
    logoutCallback();
  });
};

export const clearAuthenticationTokens = () => {
  removeItemLs("bearerToken");
  removeItemLs("refreshToken");
  removeItemLs("email");
};
