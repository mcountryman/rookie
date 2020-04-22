import * as React from "react";
import { Link } from "react-router-dom";
import Drawer from "@material-ui/core/Drawer";
import { List } from "@material-ui/core";
import ListItemText from "@material-ui/core/ListItemText";
import ListItem from "@material-ui/core/ListItem";
import ListItemIcon from "@material-ui/core/ListItemIcon";
import HomeIcon from "@material-ui/icons/Home";
import SettingsIcon from "@material-ui/icons/Settings";
import makeStyles from "@material-ui/core/styles/makeStyles";

const useStyles = makeStyles({
  root: {
    width: "100%",
    maxWidth: 560,
  }
});

interface IProps {
  isOpen: boolean;
  onClose: () => void;
}

const ListItemLink = (props: any) =>
  <ListItem
    button
    component={(inner: any) => <Link to={props.to} {...inner} />}
    {...props}
  />;

export const MainDrawer = (props: IProps) => {
  const classes = useStyles();

  return (
    <Drawer
      open={props.isOpen}
      anchor="left"
      onClose={props.onClose}>

      <div className={classes.root}>
        <List>
          <ListItemLink to="/home">
            <ListItemIcon>
              <HomeIcon/>
            </ListItemIcon>
            <ListItemText primary="Home"/>
          </ListItemLink>
          <ListItemLink to="/settings">
            <ListItemIcon>
              <SettingsIcon/>
            </ListItemIcon>
            <ListItemText primary="Settings"/>
          </ListItemLink>
        </List>
      </div>
    </Drawer>
  );
}
