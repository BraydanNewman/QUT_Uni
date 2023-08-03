import React, { useContext } from "react";
import { Nav, Navbar, NavItem } from "reactstrap";
import { EmailContext } from "../App";
import { Link } from "react-router-dom";
import { logout } from "../utils/authentication";
import { AiFillHome } from "react-icons/ai";

function ComNavbar() {
  const emailManager = useContext(EmailContext);
  return (
    <Navbar>
      <div className="navbar-brand text-light">
        <Link to="/" className="p-3">
          <AiFillHome size="2em" className="contrast-icon" />
        </Link>
        <label className="p-3">{emailManager.email}</label>
      </div>
      <Nav className="p-3">
        <NavItem>
          <Link to="/Movies/" className="nav-link">
            Movies
          </Link>
        </NavItem>
        {emailManager.email === null ? (
          <>
            <NavItem>
              <Link to="/login/" className="nav-link">
                Login
              </Link>
            </NavItem>
            <NavItem>
              <Link to="/register/" className="nav-link">
                Register
              </Link>
            </NavItem>
          </>
        ) : (
          <NavItem>
            <Link
              className="nav-link"
              to="/"
              onClick={() =>
                logout(() => {
                  emailManager.setEmail(null);
                })
              }
            >
              Logout
            </Link>
          </NavItem>
        )}
      </Nav>
    </Navbar>
  );
}

export default ComNavbar;
