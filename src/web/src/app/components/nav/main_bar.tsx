import AppBar from "@material-ui/core/AppBar";
import Toolbar from "@material-ui/core/Toolbar";
import {IconButton} from "@material-ui/core";
import MenuIcon from "@material-ui/icons/Menu";
import Typography from "@material-ui/core/Typography";
import * as React from "react";

interface IProps {
  onMenuClicked?: () => void;
}

export const MainBar = (props: IProps) => {
  return (
    <AppBar position="static">
      <Toolbar>
        <IconButton
          edge="start"
          color="inherit"
          onClick={props.onMenuClicked}
          aria-label="menu">

          <MenuIcon />
        </IconButton>
        <Typography variant="h6">
          rookie
        </Typography>
      </Toolbar>
    </AppBar>
  );
};
